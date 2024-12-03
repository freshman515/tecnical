#include<HttpClient.h>

HttpClient::HttpClient() :logger(log4cpp::Category::getRoot()) {
    log4cpp::BasicConfigurator::configure();
    logger.setPriority(log4cpp::Priority::DEBUG);
    multiHandle = curl_multi_init();
    if (!multiHandle) {
        logger.error("Failed to Initialize CURL multi handle.");
    }
}
HttpClient::~HttpClient() {
    curl_multi_cleanup(multiHandle);
    logger.info("CURL multi handle cleaned up.");
}

size_t HttpClient::write_callback(void* contents, size_t size, size_t nmemb, std::string* data) {
    data->append(reinterpret_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}
size_t HttpClient::write_data(void* contents, size_t size, size_t nmemb, FILE* file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}
size_t HttpClient::progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    if (ultotal > 0) {
        std::cout << "\rUploaded: " << ulnow << " / " << ultotal << " bytes ("
            << (ulnow * 100 / ultotal) << "%)" << std::flush;
    }
    return 0;
}
nlohmann::json HttpClient::parse_json(const std::string& rawData) {
    try {
        return nlohmann::json::parse(rawData);
    } catch (const nlohmann::json::exception& e) {
        logger.error("failed to parse JSON :" + std::string(e.what()));
        return {};
    }
}
void HttpClient::save_to_file(const std::string& fileName, nlohmann::json& jsonData) {
    try {
        std::ofstream ofs(fileName, std::ios::app);
        ofs << jsonData.dump(4);
        logger.info("JSON data saved to file " + fileName);
        ofs.close();
    } catch (const std::exception& e) {
        logger.info("failed to save JSON data :" + std::string(e.what()));
    }

}
nlohmann::json HttpClient::get(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            logger.info("GET request failed :" + std::string(curl_easy_strerror(res)));
            curl_easy_cleanup(curl);
            return {};
        }

        logger.info("GET request to URL :" + url + " completed successfually.");
        curl_easy_cleanup(curl);
    }
    return parse_json(response);
}
nlohmann::json HttpClient::post(const std::string& url, const std::string& data) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            logger.info("POST request failed :" + std::string(curl_easy_strerror(res)));
            curl_easy_cleanup(curl);
            return {};
        }

        logger.info("POST request to URL :" + url + " completed successful");
        curl_easy_cleanup(curl);
    }
    return parse_json(response);
}


void HttpClient::perform_sync_requests(std::vector<std::string>& urls, const std::string& outPutFileName) {
    std::map<CURL*, std::string*> responseMap;
    nlohmann::json combinedJson;
    for (const auto& url : urls) {
        CURL* easy_handle = curl_easy_init();
        if (easy_handle) {
            std::string* response = new std::string();
            curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, response);

            responseMap[easy_handle] = response;

            CURLMcode mc = curl_multi_add_handle(multiHandle, easy_handle);
            if (mc != CURLM_OK) {
                logger.info("Failed to add easy handle:" + std::string(curl_multi_strerror(mc)));
                curl_easy_cleanup(easy_handle);
                delete response;
            }
        } else {
            logger.info("Failed to initialize CURL easy handle for URL :" + url);

        }
    }

    int stillRuning = 0;
    int maxWaitTime = 5;
    do {
        //执行
        CURLMcode mc = curl_multi_perform(multiHandle, &stillRuning);
        if (mc != CURLM_OK) {
            logger.info("Error during curl_multi_perform :" + std::string(curl_multi_strerror(mc)));
            break;
        }

        //检查是否有已经完成的请求
        int msgsLeft = 0;
        while (CURLMsg* msg = curl_multi_info_read(multiHandle, &msgsLeft)) {
            if (msg->msg == CURLMSG_DONE) {
                CURL* easy_handle = msg->easy_handle;
                auto it = responseMap.find(easy_handle);
                if (it != responseMap.end()) {
                    std::string* response = it->second;
                    try {
                        nlohmann::json jsonData = parse_json(*response);
                        if (!jsonData.is_null()) {
                            combinedJson.push_back(jsonData);
                        }
                    } catch (...) {
                        logger.error("Error processing response.");
                    }
                    delete response;
                    responseMap.erase(it);
                }
                curl_multi_remove_handle(multiHandle, easy_handle);
                curl_easy_cleanup(easy_handle);
            }
        }
        if (stillRuning > 0) {
            struct timeval timeout;
            timeout.tv_sec = maxWaitTime;
            timeout.tv_usec = 0;

            fd_set fdRead, fdWrite, fdExcep;
            FD_ZERO(&fdRead);
            FD_ZERO(&fdWrite);
            FD_ZERO(&fdExcep);
            int maxfd = -1;

            curl_multi_fdset(multiHandle, &fdRead, &fdWrite, &fdExcep, &maxfd);

            if (maxfd == -1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                select(maxfd + 1, &fdRead, &fdWrite, &fdExcep, &timeout);
            }
        }
    } while (stillRuning);

    save_to_file(outPutFileName, combinedJson);
    logger.info("All requests completed. Result saved to " + outPutFileName);
}

bool HttpClient::download_file(const std::string& url, const std::string filename) {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* file = fopen(filename.c_str(), "wb");
        if (file == NULL) {
            logger.error("failed to open file :" + std::string(filename));
            return false;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        CURLcode res = curl_easy_perform(curl);
        fclose(file);

        if (res != CURLE_OK) {
            logger.info("CURL perform failed :" + std::string(curl_easy_strerror(res)));
            curl_easy_cleanup(curl);
            return false;
        }

    }
    curl_easy_cleanup(curl);
    logger.info("download file completed successfully!");
    return true;
}

bool HttpClient::upload_file(const std::string& url, const std::string filename) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl!" << std::endl;
        return false;
    }

    FILE* file = fopen(filename.c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    struct stat file_info;

    if (stat(filename.c_str(), &file_info) != 0) {
        logger.info("Failed to get file info");
        fclose(file);
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, file);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);  // 启用进度条

    CURLcode res = curl_easy_perform(curl);
    fclose(file);

    if (res != CURLE_OK) {
        std::cerr << "Upload failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_cleanup(curl);
    std::cout << "Upload successful!" << std::endl;

    return true;
}

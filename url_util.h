#ifndef URL_UTIL_H
#define URL_UTIL_H

#include <string>
#include <list>
#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


/**
 * @brief download_html download html from url addres
 * @param url scanning url
 * @return html code
 */
std::string download_html(const char *url, std::string *curl_type_message, std::string *curl_message)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            std::string str;
            str.append(curl_easy_strerror(res));
            *curl_type_message = "error";
            *curl_message = "curl_easy_perform() failed: " + str;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}


/**
 * @brief find_url_core
 * @param url_list list into add urls
 * @param str scanning html code
 * @param sub substring if the scaning html code
 */
static void find_url_core(std::list<std::string> *url_list, std::string *str, std::string sub)
{
    size_t pos = str->find(sub, 0);
    while(pos != std::string::npos)
    {
        char ch;
        std::string s;
        size_t index = pos;

        while (str->at(index) != '"'
               && str->at(index) != ' '
               && str->at(index) != '<'
               && str->at(index) != '\''
               && str->at(index) != ')'
               && str->at(index) != '>')
        {
            ch = str->at(index);
            s.push_back(ch);
            index++;
            if (index >= str->size()) break;
        }
        url_list->push_back(s);

        if (pos+1 >= str->size()) break;
        pos = str->find(sub,pos+1);
    }
}


std::list<std::string> find_url(std::string *str)
{
    std::list<std::string> url_list;

    find_url_core(&url_list, str, "ftp://");
    find_url_core(&url_list, str, "http://");
    find_url_core(&url_list, str, "https://");

    return url_list;
}


bool find_string(std::string * string, std::string * sub_string)
{
    size_t found;
    found = string->find(*sub_string);

    if (found!=std::string::npos){
        return true;
    }
    return false;
}

#endif // URL_UTIL_H

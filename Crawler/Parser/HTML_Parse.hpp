#ifndef HTML_PARSE
#define HTML_PARSE


#include <gumbo.h>


#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <tuple>

class HTML_Parse
{
private:
//Effective url
    std::string url;
//Effective url host
    std::string urlHost;
//Effective url path
    std::string urlPath;
//HTML document
    std::string html;
//Effective url Scheme
    std::string urlScheme;
//All urls
    std::vector<std::string> urls;
//<head> content
    std::string title;
//<meta> content
    std::string description;

    std::string allText;


    void extractUrls(GumboNode* node);

    std::string extractCleanText(GumboNode* node) const;

    std::string extractTitle(const GumboNode* root) const;

    void extractDescription(GumboNode* node);

    static std::optional<std::string> scheme(const std::string& url);

    static std::optional<std::string> path(const std::string& url);

    std::tuple<std::string, std::string, std::string> parseUrl(const std::string& url) const;

    bool isPageFragment(const std::string& url) const;
    
public:
    HTML_Parse(const std::string& url, const std::string& html);

    void parse();

    const std::vector<std::string>& getUrls() const;

    const std::string& getTitle() const;

    const std::string& getDescription() const;

    const std::string& getAllText() const;
    
};

#endif



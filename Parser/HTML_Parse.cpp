#include "HTML_Parse.hpp"

#include <gumbo.h>
#include <cassert>
#include <optional>
#include <algorithm>
#include <regex>
#include <stdexcept>

HTML_Parse::HTML_Parse(const std::string& url, const std::string& html) 
{
    this->url = url;
    this->html = html;
    
    std::tie(this->urlScheme, this->urlHost, this->urlPath) = this->parseUrl(url);
    
    if (this->urlPath.empty()) 
    {
        this->urlPath = "/";
        this->url += "/";
    }
}

void HTML_Parse::extractUrls(GumboNode* node) 
{
    if (node->type != GUMBO_NODE_ELEMENT) 
    {
        return;
    }
    
    if (node->v.element.tag == GUMBO_TAG_A) 
    {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href == nullptr || href->value == nullptr) 
        {
            return;
        }
        
        std::string parsedUrl(href->value);
        
        std::string parsedUrlScheme, parsedUrlHost, parsedUrlPath;
        std::tie(parsedUrlScheme, parsedUrlHost, parsedUrlPath) = this->parseUrl(parsedUrl);
        
        if (parsedUrlPath.empty()) 
        {
            parsedUrlPath = "/";
            parsedUrl += "/";
        }
        
        if (!(this->isPageFragment(parsedUrl))) 
        {
            if (parsedUrlScheme != "") 
            {
                if (parsedUrlScheme == this->urlScheme && parsedUrlHost == this->urlHost) 
                {
                    this->urls.push_back(parsedUrl);
                }
            } 
            else if (!parsedUrl.empty() && parsedUrl.front() == '/') 
            {
                parsedUrl = this->urlScheme + "://" + this->urlHost + parsedUrl;
                this->urls.push_back(parsedUrl);
            } 
            else 
            {
                auto backslashPosition = this->url.find_last_of("/");
                std::string url = this->url.substr(0, backslashPosition + 1);
                
                this->urls.push_back(url + parsedUrl);
            }
        }
    }
    
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) 
    {
        this->extractUrls(static_cast<GumboNode*>(children->data[i]));
    }
    
}

void HTML_Parse::parse() 
{
    GumboOutput* output = gumbo_parse(this->html.c_str());
    this->extractUrls(output->root);
    this->allText = this->extractCleanText(output->root);
    this->title = this->extractTitle(output->root);
    this->extractDescription(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

const std::vector<std::string>& HTML_Parse::getUrls() const 
{
    return this->urls;
}

const std::string& HTML_Parse::getTitle() const 
{
    return this->title;
}

const std::string& HTML_Parse::getDescription() const 
{
    return this->description;
}

const std::string& HTML_Parse::getAllText() const 
{
    return this->allText;
}

std::string HTML_Parse::extractCleanText(GumboNode* node) const 
{
    if (node->type == GUMBO_NODE_TEXT) 
    {
        return std::string(node->v.text.text);
    } 
    else if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE) 
    {
        std::string contents;
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) 
        {
            const std::string text = this->extractCleanText((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) 
            {
                contents.append(" ");
            }
            contents.append(text);
        }
        return contents;
    } 
    else 
    {
        return "";
    }
}

std::string HTML_Parse::extractTitle(const GumboNode* root) const 
{
    if (root->type != GUMBO_NODE_ELEMENT || root->v.element.children.length < 2) 
        return "";
    
    const GumboVector* rootChildren = &root->v.element.children;
    GumboNode* head = NULL;
    for (int i = 0; i < rootChildren->length; ++i) 
    {
        GumboNode* child = (GumboNode*) rootChildren->data[i];
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) 
        {
            head = child;
            break;
        }
    }
    
    if (head == NULL) 
        return "";
    
    GumboVector* head_children = &head->v.element.children;
    for (int i = 0; i < head_children->length; ++i) 
    {
        GumboNode* child = (GumboNode*) head_children->data[i];
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) 
        {
            if (child->v.element.children.length != 1) 
                return "";
            
            GumboNode* title_text = (GumboNode*) child->v.element.children.data[0];
            assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
            return title_text->v.text.text;
        }
    }
    // not found
    return "";
}

void HTML_Parse::extractDescription(GumboNode* node) 
{
    if (node->type != GUMBO_NODE_ELEMENT) 
        return;
    
    if (node->v.element.tag == GUMBO_TAG_META) 
    {
        GumboAttribute* name = gumbo_get_attribute(&node->v.element.attributes, "name");
        if (name == nullptr || name->value == nullptr || name->value != std::string("description")) 
            return;
        
        GumboAttribute* content = gumbo_get_attribute(&node->v.element.attributes, "content");
        if (content == nullptr || content->value == nullptr) 
            return;        

        this->description = content->value;
        return;
    }
    
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) 
        this->extractDescription(static_cast<GumboNode*>(children->data[i]));
    
    return;
}

std::tuple<std::string, std::string, std::string> HTML_Parse::parseUrl(const std::string& url) const 
{
    
    std::regex urlRegex (R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", std::regex::extended);
    
    std::smatch urlMatchResult;
    if (std::regex_match(url, urlMatchResult, urlRegex))   
        return std::make_tuple(*(urlMatchResult.begin() + 2), *(urlMatchResult.begin() + 4), *(urlMatchResult.begin() + 5));   
    
    return std::make_tuple("", "", "");
}

bool HTML_Parse::isPageFragment(const std::string& url) const 
{
    std::regex urlRegex (R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", std::regex::extended);
    
    std::smatch urlMatchResult;
    if (std::regex_match(url, urlMatchResult, urlRegex))    
        return !std::string(*(urlMatchResult.begin() + 8)).empty();
        
    return false;
}
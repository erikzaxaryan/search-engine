#include "SpellCorrector.hpp"

void SpellCorrector::Init()
{
    std::vector <std::pair<std::string, std::string>> rus, eng;
    nuspell::search_default_dirs_for_dicts(rus);
    nuspell::search_default_dirs_for_dicts(eng);


    auto nameAndPathRus = nuspell::find_dictionary(rus, "ru_RU");
    auto nameAndPathEng = nuspell::find_dictionary(eng, "en_US");

    auto &dict_path_rus = nameAndPathRus == end(rus) ? "" : nameAndPathRus->second;
    auto &dict_path_eng = nameAndPathEng == end(eng) ? "" : nameAndPathEng->second;

    if(dict_path_eng == "")
        this->englishDict = {};
    else
        this->englishDict = nuspell::Dictionary::load_from_path(dict_path_eng);

    if(dict_path_rus == "")
        this->russianDict = {};
    else
        this->russianDict = nuspell::Dictionary::load_from_path(dict_path_rus);
}

bool SpellCorrector::CheckQuery(const std::vector<std::string>& queryWords, std::vector<std::vector<std::string>>& suggestions)
{
    bool isCorrect = true;
    for(int i = 0; i < queryWords.size(); ++i)
    {
        if(this->englishDict.value().spell(queryWords[i]))
            continue;
        else
        {
            isCorrect = false;
            std::vector<std::string> curSugs = suggestions[i];
            this->englishDict.value().suggest(queryWords[i], curSugs);
            suggestions[i] = FilterSuggestions(queryWords[i], curSugs);
        }
    }

    return isCorrect;
}

// Get RU dictionary
std::optional<nuspell::Dictionary> SpellCorrector::getRussianDict()
{
    if(russianDict.has_value())
        return russianDict;

    return {};
}

// Get EN dictionary
std::optional<nuspell::Dictionary> SpellCorrector::getEnglishDict()
{
    if(englishDict.has_value())
        return englishDict;

    return {};
}

std::vector<std::string> SpellCorrector::FilterSuggestions(std::string baseWord, std::vector <std::string> suggestions)
{
    std::vector<std::string> result;
    int counter = 4;

    for(int i = 0; i < suggestions.size(); ++i)
    {
        if(suggestions[i].size() == baseWord.size() && counter > 0)
        {
            result.push_back(suggestions[i]);
            --counter;
        }
    }

    return result;
}
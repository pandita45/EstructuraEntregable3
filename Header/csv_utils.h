#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <filesystem>
#include <istream>
#include <string>
#include <type_traits>
#include <vector>

inline bool csvRecordHasOpenQuotes(const std::string& record) {
    bool insideQuotes = false;

    for (std::size_t i = 0; i < record.size(); ++i) {
        if (record[i] != '"') {
            continue;
        }

        if (insideQuotes && i + 1 < record.size() && record[i + 1] == '"') {
            ++i;
            continue;
        }

        insideQuotes = !insideQuotes;
    }

    return insideQuotes;
}

inline bool readCsvRecord(std::istream& input, std::string& record) {
    record.clear();

    std::string line;
    if (!std::getline(input, line)) {
        return false;
    }

    record = line;
    while (csvRecordHasOpenQuotes(record)) {
        if (!std::getline(input, line)) {
            break;
        }

        record.push_back('\n');
        record += line;
    }

    return true;
}

inline std::vector<std::string> splitCsvRecord(const std::string& record) {
    std::vector<std::string> fields;
    std::string field;
    bool insideQuotes = false;

    for (std::size_t i = 0; i < record.size(); ++i) {
        const char current = record[i];

        if (current == '"') {
            if (insideQuotes && i + 1 < record.size() && record[i + 1] == '"') {
                field.push_back('"');
                ++i;
            } else {
                insideQuotes = !insideQuotes;
            }
            continue;
        }

        if (current == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
            continue;
        }

        field.push_back(current);
    }

    fields.push_back(field);
    return fields;
}

inline std::filesystem::path resolveDatasetPath() {
    const std::filesystem::path candidates[] = {
        std::filesystem::path("Data/auspol2019.csv"),
        std::filesystem::path("../Data/auspol2019.csv")
    };

    for (const auto& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }

    return candidates[0];
}

template <typename Key>
Key parseCsvKey(const std::string& value) {
    if constexpr (std::is_integral_v<Key>) {
        return static_cast<Key>(std::stoll(value));
    } else {
        return static_cast<Key>(value);
    }
}

#endif
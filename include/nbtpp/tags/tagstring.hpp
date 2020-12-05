#ifndef TAGS_STRING_HPP_
#define TAGS_STRING_HPP_

#include "../tag.hpp"

namespace nbtpp::tags {
    class tag_string: public tag {
    public:
        tag_string(std::string name, std::string value) : tag(name, type::TAG_String), m_value(value) {
        }

        virtual ~tag_string() {
        }

        inline const std::string& getValue() const {
            return m_value;
        }

        void setMalue(const std::string& mValue) {
            m_value = mValue;
        }

    private:
        std::string m_value;
    };
} /* namespace nbtpp::tags */

#endif /* TAGS_STRING_HPP_ */

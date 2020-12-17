#ifndef TAGS_STRING_HPP_
#define TAGS_STRING_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {
        class tag_string: public tag {
        public:
            tag_string(std::string name, std::string value) : tag(name, tag_type::TAG_String), m_value(value) {
            }

            virtual ~tag_string() {
            }

            inline const std::string& value() const {
                return m_value;
            }

            void value(const std::string& mValue) {
                m_value = mValue;
            }

        private:
            std::string m_value;
        };
    }
}

#endif

#ifndef NBTPP_TAGS_TAGBYTE_HPP_
#define NBTPP_TAGS_TAGBYTE_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_byte: public tag {
        public:
            tag_byte(std::string name, int8_t value) : tag(name, tag_type::TAG_Byte), m_value(value) {

            }
            virtual ~tag_byte() {

            }

            inline const int8_t value() const {
                return m_value;
            }

            void value(int8_t mValue) {
                m_value = mValue;
            }
        private:
            int8_t m_value;
        };
    }
}

#endif

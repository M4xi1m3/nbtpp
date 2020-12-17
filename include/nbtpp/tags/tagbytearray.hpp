#ifndef NBTPP_TAGS_TAGBYTEARRAY_HPP_
#define NBTPP_TAGS_TAGBYTEARRAY_HPP_

#include "../tag.hpp"
#include <vector>

namespace nbtpp {
    namespace tags {

        class tag_bytearray: public tag {
        public:
            tag_bytearray(std::string name) : tag(name, tag_type::TAG_Byte_Array), m_value() {

            }

            virtual ~tag_bytearray() {

            }

            void append(int8_t val) {
                m_value.push_back(val);
            }

            inline const std::vector<int8_t>& value() const {
                return m_value;
            }
        private:
            std::vector<int8_t> m_value;
        };
    }
}

#endif

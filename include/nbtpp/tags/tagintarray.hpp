#ifndef NBTPP_TAGS_TAGINTARRAY_HPP_
#define NBTPP_TAGS_TAGINTARRAY_HPP_

#include "../tag.hpp"
#include <vector>

namespace nbtpp {
    namespace tags {

        class tag_intarray: public tag {
        public:
            tag_intarray(std::string name) : tag(name, tag_type::TAG_Int_Array), m_value() {

            }

            tag_intarray(std::string name, const std::vector<int32_t>& data) : tag(name, tag_type::TAG_Byte_Array), m_value(data) {

            }

            virtual ~tag_intarray() {

            }

            void append(int32_t val) {
                m_value.push_back(val);
            }

            inline const std::vector<int32_t>& value() const {
                return m_value;
            }

            inline void assign(int32_t* array, size_t count) {
                m_value.assign(array, array + count);
            }
        private:
            std::vector<int32_t> m_value;
        };

    }
}

#endif

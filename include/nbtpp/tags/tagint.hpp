#ifndef NBTPP_TAGS_TAGINT_HPP_
#define NBTPP_TAGS_TAGINT_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_int: public tag {
        public:
            tag_int(std::string name, int32_t value) : tag(name, tag_type::TAG_Int), m_value(value) {

            }
            virtual ~tag_int() {

            }

            inline const int32_t value() const {
                return m_value;
            }

            void value(int32_t mValue) {
                m_value = mValue;
            }
        private:
            int32_t m_value;
        };

    }
}

#endif

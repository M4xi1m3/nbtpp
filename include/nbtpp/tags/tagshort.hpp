#ifndef NBTPP_TAGS_TAGSHORT_HPP_
#define NBTPP_TAGS_TAGSHORT_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_short: public tag {
        public:
            tag_short(std::string name, int16_t value) : tag(name, tag_type::TAG_Short), m_value(value) {

            }
            virtual ~tag_short() {

            }

            inline const int16_t value() const {
                return m_value;
            }

            void value(int16_t mValue) {
                m_value = mValue;
            }
        private:
            int16_t m_value;
        };

    }
}

#endif

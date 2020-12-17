#ifndef NBTPP_TAGS_TAGFLOAT_HPP_
#define NBTPP_TAGS_TAGFLOAT_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_float: public tag {
        public:
            tag_float(std::string name, float value) : tag(name, tag_type::TAG_Float), m_value(value) {

            }
            virtual ~tag_float() {

            }

            inline const float value() const {
                return m_value;
            }

            void value(float mValue) {
                m_value = mValue;
            }
        private:
            float m_value;
        };

    }
}

#endif

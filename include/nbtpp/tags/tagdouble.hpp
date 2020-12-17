#ifndef NBTPP_TAGS_TAGDOUBLE_HPP_
#define NBTPP_TAGS_TAGDOUBLE_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_double: public tag {
        public:
            tag_double(std::string name, double value) : tag(name, tag_type::TAG_Double), m_value(value) {

            }
            virtual ~tag_double() {

            }

            inline const double value() const {
                return m_value;
            }

            void value(double mValue) {
                m_value = mValue;
            }
        private:
            double m_value;
        };
    }
}

#endif

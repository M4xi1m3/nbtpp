#ifndef NBTPP_TAGS_TAGINTARRAY_HPP_
#define NBTPP_TAGS_TAGINTARRAY_HPP_

#include "../tag.hpp"
#include <vector>

namespace nbtpp::tags {

    class tag_intarray: public tag {
    public:
        tag_intarray(std::string name) : tag(name, tag_type::TAG_Int_Array), m_value() {

        }

        virtual ~tag_intarray() {

        }

        void append(int32_t val) {
            m_value.push_back(val);
        }

        inline const std::vector<int32_t>& value() const {
            return m_value;
        }
    private:
        std::vector<int32_t> m_value;
    };

} /* namespace tags::nbtpp */

#endif /* NBTPP_TAGS_TAGINTARRAY_HPP_ */

#ifndef NBTPP_TAGS_TAGLIST_HPP_
#define NBTPP_TAGS_TAGLIST_HPP_

#include <vector>

#include "../tag.hpp"
#include "../nbtexception.hpp"

namespace nbtpp::tags {

    class tag_list: public tag {
    public:
        tag_list(std::string name, tag_type type) : tag(name, tag_type::TAG_List), m_type(type) {

        }

        virtual ~tag_list() {
            for (tag *t : m_content) {
                delete t;
            }
        }

        tag_type type() {
            return m_type;
        }

        void append(tag* t) {
            if (t->getType() != m_type) {
                throw nbt_exception("can't put type " + std::to_string(t->getType()) + " in list of " + std::to_string(m_type));
            }
            m_content.push_back(t);
        }

        inline const std::vector<tag*>& value() const {
            return m_content;
        }

    private:
        tag_type m_type;
        std::vector<tag*> m_content;
    };

} /* namespace tags::nbtpp */

#endif /* NBTPP_TAGS_TAGLIST_HPP_ */

#ifndef NBTPP_TAGS_TAGLIST_HPP_
#define NBTPP_TAGS_TAGLIST_HPP_

#include <vector>

#include "../nbt.hpp"
#include "../tag.hpp"
#include "../nbtexception.hpp"

namespace nbtpp {
    std::string name_for_type(tag_type t);
}

namespace nbtpp {
    namespace tags {

        class tag_list: public tag {
        public:
            tag_list(std::string name, tag_type type) : tag(name, tag_type::TAG_List), m_content_type(type) {

            }

            virtual ~tag_list() {
                for (tag *t : m_content) {
                    delete t;
                }
            }

            inline tag_type content_type() const {
                return m_content_type;
            }

            bool remove(tag* t) {
                for (auto i = m_content.begin(); i < m_content.end(); i++) {
                    if ((*i) == t) {
                        m_content.erase(i);
                        return true;
                    }
                }

                return false;
            }

            template<class T>
            T* get(int position) const {
                static_assert(std::is_base_of<nbtpp::tag, T>::value, "T must be child class of nbtpp::tag");
                return dynamic_cast<T*>(get(position));
            }

            tag* get(int position) const {
                return m_content.at(position);
            }

            void append(tag* t) {
                if (t->type() != m_content_type) {
                    throw nbt_exception("can't put type " + nbtpp::name_for_type(t->type()) + " in list of " + nbtpp::name_for_type(m_content_type));
                }
                m_content.push_back(t);
            }

            inline const std::vector<tag*>& value() const {
                return m_content;
            }

        private:
            tag_type m_content_type;
            std::vector<tag*> m_content;
        };

    }
}

#endif

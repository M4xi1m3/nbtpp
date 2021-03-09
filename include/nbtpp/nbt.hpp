#ifndef NBT_HPP_
#define NBT_HPP_

#include <iostream>
#include "tag.hpp"

namespace nbtpp {

    /**
     * Class to load NBT data
     */
    class nbt {

    public:
        enum compression : uint8_t {
            gzip = 1, zlib = 2, uncompressed = 3
        };

        /**
         * Create a blank NBT.
         */
        nbt() : m_tag(nullptr) {
        }

        /**
         * Create a NBT with an existing tag.
         */
        nbt(tag* t) : m_tag(t) {
        }

        /**
         * Loads NBT data from a file, detecting its compression (gzip'd or uncompressed) and setting the compressed flag accordingly.
         * @param in    File to load from
         */
        nbt(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream and sets the compressed flag to false.
         * @param in    Stream to load from
         */
        nbt(std::istream& in);

        /**
         * Destructor
         */
        virtual ~nbt();

        /**
         * Loads NBT data from a file, detecting its compression (gzip'd or uncompressed) and setting the compressed flag accordingly.
         * @param in    File to load from
         */
        void load_file(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream
         * @param in    Stream to load from
         */
        void load(std::istream& in);

        /**
         * Saves NBT to a file, using compression
         * @param out   File to save to
         */
        void save_file(std::ofstream& out);

        /**
         * Saves uncompressed data to a stream
         * @param out   Stream to save to
         */
        void save(std::ostream& out);

        /**
         * Retrieve the tag
         * @return
         */
        inline tag* content() const {
            return m_tag;
        }

        /**
         * Retrieve the tag
         * @return
         */
        template <class T>
        inline T* content() const {
            static_assert(std::is_base_of<nbtpp::tag, T>::value, "T must be child class of nbtpp::tag");
            return dynamic_cast<T*>(content());
        }

        /**
         * Set a new tag, delete the old one.
         * @param t
         */
        void content(tag* t) {
            if (m_tag != nullptr) {
                delete m_tag;
            }
            m_tag = t;
        }

        /**
         * Pretty prints a NBT tag to out
         */
        void debug(std::ostream& out = std::cout);

        /**
         * Get the compression method used for the NBT data
         * @return
         */
        inline compression compression_method() const {
            return m_compression;
        }

        /**
         * Set the NBT compression method
         *
         * @param type
         */
        void compression_method(compression type = uncompressed) {
            m_compression = type;
        }
    private:
        tag *m_tag;
        compression m_compression = uncompressed;
    };

    /**
     * Get name corresponding to type t
     * @param t Type to get name of
     * @return  Name of the type
     */
    std::string name_for_type(tag_type t);

}

#endif

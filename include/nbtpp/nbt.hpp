#ifndef NBT_HPP_
#define NBT_HPP_

#include <iostream>
#include "tag.hpp"
#include "stde/streams/data.hpp"

namespace nbtpp {

    /**
     * Class to load NBT data
     */
    class nbt {

    public:
        /**
         * Create a blank NBT.
         */
        nbt() : m_tag(nullptr) {
        }

        /**
         * Loads NBT data from a file, detecting its compression (gzip'd or uncompressed) and setting the compressed flag accordingly.
         * @param in    File to load from
         */
        nbt(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream and sets the compressed flag to false.
         * @param in    Stream to load from.
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
        void load(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream and sets the compressed flag to false.
         * @param in    Stream to load from.
         */
        void load(std::istream& in);

        void save(std::ostream& out);

        inline tag* getTag() const {
            return m_tag;
        }

        void debug();

        /**
         * Check if NBT was read / should be written compressed
         * @return  true if compressed, false otherwise
         */
        bool isCompressed() const {
            return m_compressed;
        }

        /**
         * Set the NBT to be written compressed.
         * @param compressed
         */
        void setCompressed(bool compressed = false) {
            m_compressed = compressed;
        }

    private:
        void debug(const tag* data, int indent);
        tag* load_internal(stde::streams::data_istream& di, tag_type force_type = tag_type::TAG_Undef);

        tag *m_tag;
        bool m_compressed = false;
    };

} /* namespace nbtpp */

#endif /* NBT_HPP_ */

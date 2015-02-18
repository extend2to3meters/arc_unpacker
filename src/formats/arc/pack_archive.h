#ifndef FORMATS_ARC_PACK_ARCHIVE
#define FORMATS_ARC_PACK_ARCHIVE
#include "formats/archive.h"

class PackArchive final : public Archive
{
public:
    PackArchive();
    ~PackArchive();
    void add_cli_help(ArgParser &) const override;
    void parse_cli_options(ArgParser &) override;
    void unpack_internal(File &, FileSaver &) const override;
private:
    struct Internals;
    std::unique_ptr<Internals> internals;
};

#endif
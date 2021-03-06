// Copyright (C) 2016 by rr-
//
// This file is part of arc_unpacker.
//
// arc_unpacker is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// arc_unpacker is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with arc_unpacker. If not, see <http://www.gnu.org/licenses/>.

#include "dec/malie/mgf_image_decoder.h"
#include "dec/png/png_image_decoder.h"

using namespace au;
using namespace au::dec::malie;

static const bstr magic = "MalieGF\x00"_b;

bool MgfImageDecoder::is_recognized_impl(io::File &input_file) const
{
    return input_file.stream.seek(0).read(magic.size()) == magic;
}

res::Image MgfImageDecoder::decode_impl(
    const Logger &logger, io::File &input_file) const
{
    io::File pseudo_file("dummy.png", input_file.stream.seek(0).read_to_eof());
    pseudo_file.stream.seek(0).write("\x89PNG\x0D\x0A\x1A\x0A"_b);
    return dec::png::PngImageDecoder().decode(logger, pseudo_file);
}

static auto _ = dec::register_decoder<MgfImageDecoder>("malie/mgf");

/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   $Id$

   class definitions for the MPEG ES/PS demultiplexer module

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __R_MPEG_ES_H
#define __R_MPEG_ES_H

#include "os.h"

#include "dts_common.h"
#include "mpeg4_common.h"
#include "pr_generic.h"
#include "smart_pointers.h"
#include "M2VParser.h"

class error_c;
class generic_reader_c;
class mm_io_c;
class track_info_c;

class mpeg_es_reader_c: public generic_reader_c {
private:
  mm_io_c *io;
  int64_t bytes_processed, size;

  int version, width, height, dwidth, dheight;
  double frame_rate, aspect_ratio;

public:
  mpeg_es_reader_c(track_info_c &_ti) throw (error_c);
  virtual ~mpeg_es_reader_c();

  virtual file_status_e read(generic_packetizer_c *ptzr, bool force = false);
  virtual int get_progress();
  virtual void identify();
  virtual void create_packetizer(int64_t id);

  static bool read_frame(M2VParser &parser, mm_io_c &in, int64_t max_size = -1, bool flush_parser = false);

  static int probe_file(mm_io_c *io, int64_t size);
};

#endif // __R_MPEG_ES_H
/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   class definitions for the AAC demultiplexer module

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __R_AAC_H
#define __R_AAC_H

#include "common/common_pch.h"

#include <stdio.h>

#include "common/aac.h"
#include "common/error.h"
#include "common/mm_io.h"
#include "merge/pr_generic.h"

class aac_reader_c: public generic_reader_c {
private:
  unsigned char *chunk;
  mm_io_c *io;
  int64_t bytes_processed, size;
  bool emphasis_present;
  aac_header_t aacheader;
  bool sbr_status_set;

public:
  aac_reader_c(track_info_c &_ti) throw (error_c);
  virtual ~aac_reader_c();

  virtual file_status_e read(generic_packetizer_c *ptzr, bool force = false);
  virtual void identify();
  virtual int get_progress();
  virtual void create_packetizer(int64_t id);

  static int probe_file(mm_io_c *io, uint64_t size, int64_t probe_range, int num_headers);

protected:
  virtual void guess_adts_version();
  static int find_valid_headers(mm_io_c *io, int64_t probe_range, int num_headers);
};

#endif // __R_AAC_H

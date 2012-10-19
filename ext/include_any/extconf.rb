require 'mkmf'

$CFLAGS += ' -std=c99 -Wall -pedantic '

ext_name = 'include_any/include_any'
create_makefile(ext_name)

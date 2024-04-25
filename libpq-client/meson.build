project('hello_libpq', 'c')

cc = meson.get_compiler('c')
lib_pq = cc.find_library('pq', dirs: ['/home/ldd/opt/pgsql/lib'])
inc_pq = include_directories('/home/ldd/opt/pgsql/include')

executable('hello', 'hello.c',
  dependencies: [lib_pq],
  include_directories: inc_pq)

executable('simple_query', 'simple_query.c',
  dependencies: [lib_pq],
  include_directories: inc_pq)

executable('cursor', 'cursor.c',
  dependencies: [lib_pq],
  include_directories: inc_pq)

executable('conn_shared', 'conn_shared.c',
  dependencies: [lib_pq],
  include_directories: inc_pq)

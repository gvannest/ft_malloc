#!/usr/bin/sh

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES='libft_malloc.so'
export DYLD_FORCE_FLAT_NAMESPACE=1

exa -liaR ~
# ls -Rgals /
# ./test
# ag malloc ~

# env DYLD_LIBRARY_PATH=.
# env DYLD_INSERT_LIBRARIES='libft_malloc.so'
# env DYLD_FORCE_FLAT_NAMESPACE=1

# g_ptr.tiny_free_begin
# g_ptr.small_free_begin
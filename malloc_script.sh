#!/usr/bin/sh

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES='libft_malloc.so'
export DYLD_FORCE_FLAT_NAMESPACE=1

$@
# exa -lisaR ~
ls -Rgalis /
#ls -R /tmp
# ./tests
# ag malloc ~
#open -a /Users/gvannest/Google\ Chrome.app/Contents/MacOS/Google\ Chrome
#open -a firefox
# /Applications/Spotify.app/Contents/MacOS/Spotify
#/Applications/Firefox.app/Contents/MacOS/firefox
#/Applications/TextEdit.app/Contents/MacOS/TextEdit
#/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome

# env DYLD_LIBRARY_PATH=.
# env DYLD_INSERT_LIBRARIES='libft_malloc.so'
# env DYLD_FORCE_FLAT_NAMESPACE=1

# g_ptr.tiny_free_begin
# g_ptr.small_free_begin
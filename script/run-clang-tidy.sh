#!/bin/bash -e

THISDIR="$(dirname "${BASH_SOURCE[0]}")"
ROOTDIR="$(realpath "${THISDIR}/..")"

pecho(){
    echo "${@}" 1>&2
}

help_and_exit(){
    p="echo"
    $p "Script for running clang-tidy"
    $p ""
    $p "Usage: $0 [options] [files...]"
    $p ""
    $p "Options:"
    $p " -c --changed-from [ref]  Run against files that have changed from git ref"
    $p " -h --help                Print this help and exit"
    $p " -j --jobs [no]           How many jobs ro run in parallel. Default is '$(nproc)'"
    $p " -s --staged              Run for files with staged changes"
    $p " -u --unstaged            Run for files with unstaged changes"
    exit 0
}

unstaged_changes(){
    (
    cd "${ROOTDIR}"
    realpath -m $(git diff --name-only)
    )
}

staged_changes(){
    (
    cd "${ROOTDIR}"
    realpath "$(git diff --staged --name-only)"
    )
}

changed_from(){
    src="${1}"
    (
    cd "${ROOTDIR}"
    realpath "$(git diff --name-only "${src}..HEAD")"
    )
}

filter_existing(){
    out=""
    for f in "${@}"; do
        [ -f "${f}" ] && out="${out} ${f}"
    done
    echo ${out}
}

filter_cpp(){
    out=""
    for f in "${@}"; do
        case "$f" in
            *.hpp|*.cpp)
                out="${out} ${f}"
                ;;
        esac
    done
    echo "${out}"
}

SRCS=""

J="$(nproc)"

while [ $# -gt 0 ]; do
    case "${1}" in
        -c|--changed-from)
            SRCS="${SRCS} $(changed_from "${2}")"
            shift
            ;;
        -h|--help)
            help_and_exit
            ;;
        -j|--jobs)
            J="${2}"
            shift
            ;;
        -s|--staged)
            SRCS="${SRCS} $(staged_changes)"
            ;;
        -u|--unstaged)
            SRCS="${SRCS} $(unstaged_changes)"
            ;;
        *)
            SRCS="${SRCS} ${1}"
    esac
    shift
done

SRCS="$(filter_existing ${SRCS})"
SRCS="$(filter_cpp ${SRCS})"


pecho "Running for ${SRCS}"
# shellcheck disable=SC2086
parallel "-j${J}" clang-tidy -p "${ROOTDIR}/build" ::: ${SRCS}


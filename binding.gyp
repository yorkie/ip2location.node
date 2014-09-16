{
  "targets": [
    {
      "target_name": "ip2location",
      "sources": [
        "src/IP2Loc_DBInterface.c",
        "src/IP2Location.c",
        "src/api.cc",
      ],
      "cflags": [
        "-Wno-trigraphs"
      ],
      "defines": [
        "HAVE_SNPRINTF"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    },
  ]
}
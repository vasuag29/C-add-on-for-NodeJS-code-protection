{
    "targets": [
      {
        "target_name": "nodeaddon",
        "sources": [ "addon_source.cc" ],
        "include_dirs" : [
          "<!(node -e \"require('nan')\")"
        ]
      }
    ]
  }

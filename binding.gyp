{
  "targets": [{
    "target_name": "editorVersion",
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "fetchUnityVersion.cc"
    ]
  }]
}
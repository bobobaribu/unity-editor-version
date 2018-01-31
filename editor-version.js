var editorVersion

if (process.env.DEBUG) {
    editorVersion= require('./build/Debug/editorVersion.node')
} else {
    editorVersion= require('./build/Release/editorVersion.node')
}

module.exports = editorVersion
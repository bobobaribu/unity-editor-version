// fetchUnityVersion.cpp : Defines the entry point for the console application.
//

#include <nan.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace v8;
using namespace node;

#define THROW_BAD_ARGS Nan::ThrowTypeError("Bad argument")

NAN_MODULE_INIT(InitModule) {

}

#ifdef _WIN32
// returns NULL if the value could not be obtained
wchar_t *GetUnityVersion(const wchar_t *szFilename)
{
	// allocate a block of memory for the version info
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize(szFilename, &dummy);
	if (dwSize == 0)
	{
		return NULL;
	}
	BYTE *data = new BYTE[dwSize];

	// load the version info
	if (!GetFileVersionInfo(szFilename, NULL, dwSize, &data[0]))
	{
		delete[] data;
		return NULL;
	}

	wchar_t *pvUnityVersion = NULL;
	unsigned int iUnityVersionLen = 0;

	if (!VerQueryValue(&data[0], _T("\\StringFileInfo\\040904b0\\Unity Version"), (LPVOID *)&pvUnityVersion, &iUnityVersionLen))
	{
		delete[] data;
		return NULL;
	}

	wchar_t *ret = new wchar_t[iUnityVersionLen];
	memcpy(ret, pvUnityVersion, iUnityVersionLen * sizeof(wchar_t));
	delete[] data;
	return ret;
}
#endif

static NAN_METHOD(GetUnityVersion) {
  if (info.Length() < 1 ||
      !info[0]->IsString() ) {
    return THROW_BAD_ARGS;
  }

  String::Utf8Value path(info[0]->ToString());

  // Synchronous call needs much less work
  if (!info[1]->IsFunction()) {
#ifdef _WIN32
    wchar_t *unityVersion = GetUnityVersion(path);
	info.GetReturnValue().Set(Nan::New<String>(unityVersion));
#else
    info.GetReturnValue().SetUndefined();
#endif
    return;
  }

/*
// overkill to create a promise for now...

  store_data_t* statvfs_data = new store_data_t();

  statvfs_data->cb = new Nan::Callback((Local<Function>) info[1].As<Function>());
  statvfs_data->fs_op = FS_OP_STATVFS;
  statvfs_data->path = strdup(*path);

  uv_work_t *req = new uv_work_t;
  req->data = statvfs_data;
  uv_queue_work(uv_default_loop(), req, EIO_StatVFS,(uv_after_work_cb)EIO_After);
*/
  info.GetReturnValue().SetUndefined();
}

extern "C"
NAN_MODULE_INIT(init)
{

}


NODE_MODULE(editorVersion, init);
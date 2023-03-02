#pragma once

#define CG_DELETE(ptr)     { if (ptr) { delete (ptr);     (ptr) = nullptr; } }
#define CG_DELETE_ARR(ptr) { if (ptr) { delete[] (ptr);   (ptr) = nullptr; } }
#define CG_RELEASE(ptr)    { if (ptr) { (ptr)->Release(); (ptr) = nullptr; } }
#define CG_CLOSE(ptr)      { if (ptr) { (ptr)->Close(); delete (ptr); (ptr) = nullptr; } }


#define CG_MAJOR_VERSION_    0x1
#define CG_MINOR_VERSION_    0x0
#define CG_REVISION_VERSION_ 0x0
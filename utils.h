#pragma once
#include <fstream>
#include <sstream>

#include "variant.h"
namespace utils
{
	class StringUtils
	{
	public:
		static std::string wStringToString(const std::wstring& str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			return converter.to_bytes(str);
		}

		static std::wstring stringToWString(const std::string& str)
		{

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			return converter.from_bytes(str);
		}

		static std::string removeSpaces(std::string str)
		{
			str.erase(std::remove_if(str.begin(), str.end(), isspace));
			return str;
		}

	};

	class FileUtils
	{
	public:
		static std::string readFile(std::string path)
		{
			std::ifstream ifs(path.c_str(), std::ifstream::in);
			if (!ifs.is_open())
			{
				std::cerr << "Could not open file " << std::endl;
				throw std::exception();
			}

			std::stringstream buffer;
			buffer << ifs.rdbuf();
			return buffer.str();
		}


		/* Returns a list of files in a directory (except hidden one) */
		static std::vector<std::string> getFilesInDirectory(const std::string directory)
		{
			std::vector<std::string> result;
			HANDLE dir;
			WIN32_FIND_DATA fileData;

			if ((dir = FindFirstFile(utils::StringUtils::stringToWString((directory + "/*")).c_str(), &fileData)) == INVALID_HANDLE_VALUE)
			{
				/* No files found */
				return result;
			}

			do
			{
				const std::string fileName = utils::StringUtils::wStringToString(fileData.cFileName);
				const bool isDirectory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

				if (fileName[0] == '.')
					continue;

				if (isDirectory)
					continue;

				result.push_back(fileName);
			} while (FindNextFile(dir, &fileData));

			FindClose(dir);
			return result;
		}


		/* Returns a list of folders in a directory (except the ones that begin with a dot) */
		static std::vector<std::string> getFoldersInDirectory(const std::string directory)
		{
			std::vector<std::string> result;
			HANDLE dir;
			WIN32_FIND_DATA fileData;

			if ((dir = FindFirstFile(utils::StringUtils::stringToWString((directory + "/*")).c_str(), &fileData)) == INVALID_HANDLE_VALUE)
			{
				return result; /* No files found */
			}

			do
			{
				const std::string fileName = utils::StringUtils::wStringToString(fileData.cFileName);
				const bool isDirectory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

				if (fileName[0] == '.')
					continue;

				if (isDirectory)
					result.push_back(fileName);

			} while (FindNextFile(dir, &fileData));

			FindClose(dir);
			return result;
		}

		static std::string getCurrentDirectory()
		{
			char cCurrentPath[FILENAME_MAX];

			if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
			{
				return "";
			}
			return cCurrentPath;
		}

	};

	class CefUtils
	{
	public:
		static std::vector<Variant> cefListToVariantList(CefRefPtr<CefListValue> cefList)
		{
			std::vector<Variant> variantList;
			for (std::size_t i = 0; i < cefList->GetSize(); i++)
			{
				switch (cefList->GetType(i))
				{
				case VTYPE_INT:
					variantList.push_back(Variant(cefList->GetInt(i)));
					break;
				case VTYPE_DOUBLE:
					variantList.push_back(Variant((float)cefList->GetDouble(i)));
					break;
				case VTYPE_BOOL:
					variantList.push_back(Variant(cefList->GetBool(i)));
					break;
				case VTYPE_STRING:
					variantList.push_back(Variant(cefList->GetString(i)));
					break;
				default: 
					break;
				}
			}
			return variantList;
		}

		static CefV8ValueList cefListValueToCefV8ValueList(CefRefPtr<CefListValue> listValue)
		{
			CefV8ValueList v8ValueList;
			for (unsigned int i = 0; i < listValue->GetSize(); i++)
			{
				v8ValueList.push_back(cefValueToV8Value(listValue->GetValue(i)));
			}
			return v8ValueList;
		}

		static CefRefPtr<CefV8Value> cefValueToV8Value(CefRefPtr<CefValue> value)
		{
			CefRefPtr<CefV8Value> result;
			switch (value->GetType())
			{
			case VTYPE_INT:
				result = CefV8Value::CreateInt(value->GetInt());
				break;
			case VTYPE_DOUBLE:
				result = CefV8Value::CreateDouble(value->GetDouble());
				break;
			case VTYPE_BOOL:
				result = CefV8Value::CreateBool(value->GetBool());
				break;
			case VTYPE_STRING:
				result = CefV8Value::CreateString(value->GetString());
				break;
			default:
				break;
			}
			return result;
		}

		static CefRefPtr<CefValue> variantToCefValue(Variant variant)
		{
			CefRefPtr<CefValue> result = CefValue::Create();
			switch (variant.getType())
			{
			case Int:
				result->SetInt(variant.getIntValue());
				break;
			case Bool:
				result->SetBool(variant.getBoolValue());
				break;
			case String:
				result->SetString(variant.getStringValue());
				break;
			case Float:
				result->SetDouble((double)variant.getFloatValue());
				break;
			default: 
				break;
			}
			return result;
		}
	};

	class ProcessUtils
	{
	public:
		static bool isProcessStarted(std::string processName)
		{
			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			{
				return false;
			}

			// Calculate how many process identifiers were returned.
			cProcesses = cbNeeded / sizeof(DWORD);
			bool processFound = false;
			for (i = 0; i < cProcesses && !processFound; i++)
			{
				if (aProcesses[i] != 0)
				{
					if (processName == getProcessName(aProcesses[i]))
					{
						processFound = true;
					}
				}
			}

			return processFound;
		}

		static std::string getProcessName(DWORD processID)
		{
			TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

			// retrieve a handle to the process.
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

			// retrieve the process name.
			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
				{
					GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
				}
			}

			// release the handle to the process.
			CloseHandle(hProcess);

			return utils::StringUtils::wStringToString(szProcessName);
		}
	};

	class SFMLUtils
	{
	public:
		static bool isColorNear(sf::Color a, sf::Color b, int offset)
		{
			return a.r <= b.r + offset && a.r >= b.r - offset
				&& a.g <= b.g + offset && a.g >= b.g - offset
				&& a.b <= b.b + offset && a.b >= b.b - offset
				&& a.a <= b.a + offset && a.a >= b.a - offset;
		}
	};

	class WindowUtils
	{
	public:
		static sf::Image captureImageFromWindow(HWND handle)
		{
			HDC hdcWindow;
			HDC hdcMemDC = NULL;
			HBITMAP hbmScreen = NULL;
			BITMAP bmpScreen;
			sf::Vector2i size;

			sf::Image image;
			sf::Texture texture;
			// Retrieve the handle to a display device context for the client 
			// area of the m_window.
			hdcWindow = GetDC(handle);

			// Create a compatible DC which is used in a BitBlt from the m_window DC
			hdcMemDC = CreateCompatibleDC(hdcWindow);
			if (!hdcMemDC)
			{
				MessageBox(handle, L"CreateCompatibleDC has failed", L"Failed", MB_OK);
				goto done;
			}

			// Get the client area for size calculation
			RECT rcClient;
			GetClientRect(handle, &rcClient);
			size.x = rcClient.right - rcClient.left;
			size.y = rcClient.bottom - rcClient.top;
			//This is the best stretch mode
			SetStretchBltMode(hdcWindow, HALFTONE);

			// Create a compatible bitmap from the Window DC
			hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

			if (!hbmScreen)
			{
				MessageBox(handle, L"CreateCompatibleBitmap Failed", L"Failed", MB_OK);
				goto done;
			}

			// Select the compatible bitmap into the compatible memory DC.
			SelectObject(hdcMemDC, hbmScreen);

			// Bit block transfer into our compatible memory DC.
			if (!BitBlt(hdcMemDC,
				0, 0,
				rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
				hdcWindow,
				0, 0,
				SRCCOPY))
			{
				MessageBox(handle, L"BitBlt has failed", L"Failed", MB_OK);
				goto done;
			}

			// Get the BITMAP from the HBITMAP
			GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

			BITMAPINFOHEADER   bi;

			bi.biSize = sizeof(BITMAPINFOHEADER);
			bi.biWidth = bmpScreen.bmWidth;
			bi.biHeight = bmpScreen.bmHeight;
			bi.biPlanes = 1;
			bi.biBitCount = 32;
			bi.biCompression = BI_RGB;
			bi.biSizeImage = 0;
			bi.biXPelsPerMeter = 0;
			bi.biYPelsPerMeter = 0;
			bi.biClrUsed = 0;
			bi.biClrImportant = 0;

			DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

			// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
			// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
			// have greater overhead than HeapAlloc.
			HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
			BYTE *lpbitmap = (BYTE *)GlobalLock(hDIB);

			// Gets the "bits" from the bitmap and copies them into a buffer 
			// which is pointed to by lpbitmap.
			GetDIBits(hdcWindow, hbmScreen, 0,
				(UINT)bmpScreen.bmHeight,
				lpbitmap,
				(BITMAPINFO *)&bi, DIB_RGB_COLORS);

			image.create(size.x, size.y);
			for (int i = 0; i < size.x; i++)
			{
				for (int j = 0; j < size.y; j++)
				{
					sf::Color color;
					color.b = (int)lpbitmap[4 * ((j*size.x) + i)];
					color.g = (int)lpbitmap[4 * ((j*size.x) + i) + 1];
					color.r = (int)lpbitmap[4 * ((j*size.x) + i) + 2];
					image.setPixel(i, (size.y - 1) - j, color);
				}
			}

			//Unlock and Free the DIB from the heap
			GlobalUnlock(hDIB);
			GlobalFree(hDIB);

			//Clean up
		done:
			DeleteObject(hbmScreen);
			DeleteObject(hdcMemDC);
			ReleaseDC(handle, hdcWindow);

			//texture.loadFromImage(image);
			return image;
		}
	};
}
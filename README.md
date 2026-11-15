# TIFF Tools X
Two WSH scripts used for **creating or splitting multi-page TIFF files**. Plus, a COM component used by scripts to open [Common File Dialogs](https://learn.microsoft.com/en-us/windows/win32/shell/common-file-dialog). An improved version of the former [TIFF Tools repository](https://github.com/javadbayat/tifftools).

This product consists of the three files `maketiffX.js`, `splittiffX.js`, and `CommonFileDialog.dll`. You obtain the latter DLL file by compiling the C++ source code in this repository.

This product is based on the **Active Station** technology. Therefore, to compile the source code of `CommonFileDialog.dll`, it is required that the static library files `libstation.x86.lib` and `libstation.x64.lib` be present in the project directory. To obtain these files, head to [the ActiveStation repository](https://github.com/javadbayat/ActiveStation), and compile the static library's source code from that repository.

## Usage
Unlike its predecessor, this version of **TIFF Tools** doesn't require that you specify the input or output file paths on the command line. Instead, it displays **Common File Dialogs** that let you select your files via a GUI.

To split a multi-page TIFF file into separate image files, right-click on the script `splittiffX.js` and choose **Open with Command Prompt** from the context menu. Then **a Browse dialog box** pops up, letting you select **the TIFF file** that is to be splitted. After selecting the TIFF file, another **Browse dialog box** appears, asking you to select the folder where **the pages as separate image files** are to be saved.

To merge several regular image files into one multi-page TIFF file, right-click on the script `maketiffX.js` and choose **Open with Command Prompt** from the context menu. Then **a Browse dialog box** pops up, asking you to select **the image files that are to be merged**. After selecting them, another **Browse dialog box** appears, asking you to select where **the resulting multi-page TIFF file** is to be saved.

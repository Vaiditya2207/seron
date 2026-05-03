include(FetchContent)

function(checkout_layer_shell_qt)
	set(FETCHCONTENT_QUIET OFF)
	set(LAYER_SHELL_QT_DECLARATIVE OFF)

	FetchContent_Declare(
	  layer-shell-qt
	  EXCLUDE_FROM_ALL
	  GIT_REPOSITORY https://github.com/KDE/layer-shell-qt
	)

	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

	FetchContent_MakeAvailable(layer-shell-qt)

	# Fix missing umbrella headers in BUILD_INTERFACE include path
	set(_lsq_inc ${layer-shell-qt_BINARY_DIR}/src/LayerShellQt)
	file(CREATE_LINK ${layer-shell-qt_BINARY_DIR}/src/Window ${_lsq_inc}/Window SYMBOLIC)
	file(CREATE_LINK ${layer-shell-qt_BINARY_DIR}/src/Shell  ${_lsq_inc}/Shell  SYMBOLIC)
	file(CREATE_LINK ${layer-shell-qt_SOURCE_DIR}/src/interfaces/window.h ${_lsq_inc}/window.h SYMBOLIC)
	file(CREATE_LINK ${layer-shell-qt_SOURCE_DIR}/src/interfaces/shell.h  ${_lsq_inc}/shell.h  SYMBOLIC)
endfunction()

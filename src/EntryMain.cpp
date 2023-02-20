// Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#include <App.h>

int main(int argc, char* argv[])
{
	qputenv("QT3D_RENDERER", "opengl");
	qputenv("QSG_RHI_BACKEND", "opengl");
    return ver::App{ argc, argv }.Start();
}

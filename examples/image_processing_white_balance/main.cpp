/*

PICCANTE Examples
The hottest examples of Piccante:
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3.0 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    See the GNU Lesser General Public License
    ( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.
*/

//This means that we disable Eigen; some functionalities cannot be used.
//For example, estimating the camera response function
#define PIC_DISABLE_EIGEN

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;

    if(argc == 2) {
        img_str = argv[1];
    } else {
        img_str = "../data/input/tommaseo_statue.png";
    }

    printf("Reading images...");
    pic::Image img(img_str, pic::LT_NOR_GAMMA);
    printf("Is the image valid? ");

    if(img.isValid()) {
        pic::Image *out = pic::FilterWhiteBalance::execute(&img, 200, 200, true);

        std::string name = pic::removeExtension(img_str);
        name = pic::removeLocalPath(name);

        bool bWrite = out->Write("../data/output/" + name + "_wb.png", pic::LT_NOR_GAMMA, 0);

        if(!bWrite) {
            printf("The image could not be written.\n");
        }

        if(out != NULL) {
            delete out;
        }

        return bWrite ? 1 : 0;
    } else {
        printf("The image could not be read.\n");
        return 0;
    }

    return 0;
}

#ifndef GRAPHICSCPP_FILESYSTEM_H
#define GRAPHICSCPP_FILESYSTEM_H

std::string ReadFile(const char *fileName);

unsigned char *LoadImage(const char *name, int *w, int *h, int *nrChannel);

void FreeImage(unsigned char *data);

#endif //GRAPHICSCPP_FILESYSTEM_H
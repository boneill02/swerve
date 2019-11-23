#ifndef DEVICE_H
#define DEVICE_H

struct device_s {
	void *(*read)(struct device_s *, size_t);
	void (*write)(struct device_s *, void *, size_t);
};

typedef struct device_s Device;

#endif

/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef BMI260_H_
#define BMI260_H_

#include <linux/iio/iio.h>
#include <linux/regulator/consumer.h>

enum bmi260_int_pin {
	BMI260_PIN_INT1,
	BMI260_PIN_INT2
};

struct bmi260_config {
	int accel_scale;
	int accel_odr;
	int accel_uodr;
	int gyro_scale;
	int gyro_odr;
	int gyro_uodr;
	bool irq;
	bool suspended;
};

struct bmi260_data {
	struct regmap *regmap;
	struct iio_trigger *trig;
	struct regulator_bulk_data supplies[2];
	struct iio_mount_matrix orientation;
	enum bmi260_int_pin int_pin;
	bool use_spi;
	struct bmi260_config conf;

	/*
	 * Ensure natural alignment for timestamp if present.
	 * Max length needed: 2 * 3 channels + 4 bytes padding + 8 byte ts.
	 * If fewer channels are enabled, less space may be needed, as
	 * long as the timestamp is still aligned to 8 bytes.
	 */
	__le16 buf[12] __aligned(8);
};

extern const struct regmap_config bmi260_regmap_config;

int bmi260_core_probe(struct device *dev, struct regmap *regmap,
		      int irq, const char *name, bool use_spi);

int bmi260_enable_irq(struct regmap *regmap, enum bmi260_int_pin pin, bool enable);

int bmi260_probe_trigger(struct iio_dev *indio_dev, int irq, u32 irq_type);

extern const struct dev_pm_ops bmi260_pm_ops;

#endif  /* BMI260_H_ */

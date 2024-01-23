# BMI260 IMU driver

This is a kernel module driver for the Bosch BMI260 IMU. This module is based off of the existing kernel BMI160 implementation. The 260 appears to follow the same specifications as the 270, or close enough to work at least. The configuration binary comes from [Chromium OS](https://chromium.googlesource.com/chromiumos/platform/ec/+/2adede07783d40c6115a96f5f70dbf94ea9a2215/third_party/bmi260/accelgyro_bmi260_config_tbin.h).

Currently only i2c connections are supported, SPI may come later.

# Installation
To install, you may use the AUR package `bmi260-dkms` which builds from this 
repository, or install this repository as a dkms package.

## Arch Install
Install from the Arch User Repository 
([AUR](https://aur.archlinux.org/packages/bmi260-dkms)).
```bash
yay -S bmi260-dkms
pikaur -S bmi260-dkms
# etc....
```

## ❄️ NixOS 

Using nix flakes support

There is a NUR module maintained by [@Cryolitia](https://github.com/Cryolitia)
```
{
  description = "NixOS configuration with flakes";
  inputs.cryolitia-nur.url = "github:Cryolitia/nur-packages/master";

  outputs = { self, nixpkgs, cryolitia-nur }: {
    # replace <your-hostname> with your actual hostname
    nixosConfigurations.<your-hostname> = nixpkgs.lib.nixosSystem {
      # ...
      modules = [
        # ...
        cryolitia-nur.nixosModules.bmi260
        hardware.sensor.iio.bmi260.enable = true;
      ];
    };
  };
}
```

## Other Distributions
You can also install as a DKMS package manually if you are on Fedora or another distro.
```bash
sudo git clone https://github.com/hhd-dev/bmi260 /usr/src/bmi260-0.0.1
cd /usr/src/bmi260-0.0.1

sudo sed -e "s/@_PKGBASE@/bmi260/" \
    -e "s/@PKGVER@/0.0.1/" \
    -i dkms.conf

sudo dkms install bmi260/0.0.1
```

To uninstall:
```bash
sudo dkms uninstall bmi260/0.0.1
sudo rm -r /usr/src/bmi260-0.0.1
```

# License
The driver in this repository is licensed under GPL-2.0-only, following the driver it is based on (for the Bosch 160). 

The configuration blob that is uploaded to the BMI 260 is sourced from ChromeOS and licensed under BSD-3-Clause.

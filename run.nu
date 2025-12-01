#!/bin/nu

cd ./hello1

with-env {
    PATH: ($env.PATH | prepend "/home/vanya/vault/kpi/study/semester5/ak/toolchains/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin"),
    CROSS_COMPILE: "ccache arm-linux-gnueabihf-",
    ARCH: "arm",
    KDIR: "/home/vanya/vault/kpi/study/semester5/ak/shared/linux-stable",
} {
    make
}

cp lab5hello1.ko ../../../shared/busybox/_install/bin/

cd ..

cd ./hello2

with-env {
    PATH: ($env.PATH | prepend "/home/vanya/vault/kpi/study/semester5/ak/toolchains/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin"),
    CROSS_COMPILE: "ccache arm-linux-gnueabihf-",
    ARCH: "arm",
    KDIR: "/home/vanya/vault/kpi/study/semester5/ak/shared/linux-stable",
} {
    make
}

cp lab5hello2.ko ../../../shared/busybox/_install/bin/

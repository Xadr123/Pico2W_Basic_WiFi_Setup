// Helpful references
// https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
// https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
// https://www.i-programmer.info/programming/148-hardware/16031-the-picow-in-c-a-better-connect.html
// https://github.com/raspberrypi/pico-examples/tree/master/pico_w


#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "config.h" // see sample.config.h
// #include "lwipopts.h" - This file is not provided in the SDK. You must make this yourself or use the given example, however you do not need to specify the include.
// for some reason this header cannot be in the src/ folder.

uint32_t Country = CYW43_COUNTRY_USA; // Append country to the end (replace USA if not USA)
uint32_t AuthType = CYW43_AUTH_WPA2_AES_PSK; // Other Auth types: CYW43_AUTH_OPEN, CYW43_AUTH_WPA_TKIP_PSK, CYW43_AUTH_WPA2_MIXED_PSK

void initWifi(const char *ssid, const char *password, uint32_t country, uint32_t auth)
{
    // Initialize onboard wifi chip with specified country settings
    // Variations:
    // cyw43_arch_init () - initialize with default country
    if (cyw43_arch_init_with_country(country))
    {
        printf("Wi-Fi init failed\n");
        return;
    }

    printf("Wi-Fi initialized\n");
    
    // Enable client mode
    // Variations:
    // cyw43_arch_enable_ap_mode(ssid, password, auth) - enables server mode (access point)
    cyw43_arch_enable_sta_mode();

    // Connect to a network or timeout in 10 seconds.
    // Variations:
    // cyw43_arch_wifi_connect_timeout_ms(ssid, password, auth, waitTime)
    // cyw43_arch_wifi_connect_async(ssid, password, auth)
    if (cyw43_arch_wifi_connect_blocking(ssid, password, auth))
    {
        printf("Wi-Fi connection failed\n");
        return;
    }

    printf("Wi-Fi connected\n");

    // Turn on the LED if everything succeeds.
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}


int main()
{
    stdio_init_all();

    initWifi(ssidName, ssidPassword, Country, AuthType);

    while (true) {
        printf("Wifi Functional!\n");
        sleep_ms(1000);
    }
}

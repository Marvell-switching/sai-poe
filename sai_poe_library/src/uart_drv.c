/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

/*! General definitions */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include <h/uart_drv.h>
#include <h/utils/log.h>


#define POE_PD69200_MSG_LEN          (15)
#define POE_PD69200_MSG_CSUM_LEN     (2)
#define POE_PD69200_MSG_N            (0x4E)
#define POE_PD69200_COMM_RETRY_TIMES (6)
#define POE_PD69200_COMM_DELAY_MS    (50)

#define MSG_BYTES "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x"
#define MSG_TO_PRINT(_A) _A[0], _A[1], _A[2], _A[3], _A[4], _A[5], _A[6], _A[7], _A[8], _A[9], _A[10], _A[11], _A[12], _A[13], _A[14]

struct UartDevice {
    char filename[64];
    int rate;
    int fd;
    struct termios tty;
};

struct __attribute__((__packed__)) poe_msg_t {
    uint8_t key;
    uint8_t echo;
    uint8_t sub;
    uint8_t sub1;
    uint8_t data[9];
    uint8_t checksum[2];
};

struct __attribute__((__packed__)) poe_port_status_msg_t {
    uint8_t key;            // KEY
    uint8_t echo;           // ECHO
    uint8_t status;         // SUB
    uint8_t enabled;        // SUB1
    uint8_t sub2;           // SUB2
    uint8_t opmode;         // DATA5
    uint8_t _data6;         // DATA6
    uint8_t priority;       // DATA7
    uint8_t _data8;         // DATA8
    uint8_t _data9;         // DATA9
    uint8_t _data10;        // DATA10
    uint8_t _data11;        // DATA11
    uint8_t _data12;        // DATA12
    uint8_t checksum[2];    // CSUM
};

struct __attribute__((__packed__)) poe_port_class_msg_t {
    uint8_t key;            // KEY
    uint8_t echo;           // ECHO
    uint8_t sub;            // SUB
    uint8_t sub1;           // SUB1
    uint8_t measured_class; // SUB2
    uint8_t _data5;         // DATA5
    uint8_t _data6;         // DATA6
    uint8_t _data7;         // DATA7
    uint8_t class;          // DATA8
    uint8_t power_limit_h;  // DATA9
    uint8_t power_limit_l;  // DATA10
    uint8_t _data11;        // DATA11
    uint8_t _data12;        // DATA12
    uint8_t checksum[2];    // CSUM
};

struct __attribute__((__packed__)) poe_port_measurement_msg_t {
    uint8_t key;            // KEY
    uint8_t echo;           // ECHO
    uint8_t sub;            // SUB
    uint8_t sub1;           // SUB1
    uint8_t current_h;      // SUB2
    uint8_t current_l;      // DATA5
    uint8_t consump_h;      // DATA6
    uint8_t consump_l;      // DATA7
    uint8_t _data8;         // DATA8
    uint8_t voltage_h;      // DATA9
    uint8_t voltage_l;      // DATA10
    uint8_t _data11;        // DATA11
    uint8_t _data12;        // DATA12
    uint8_t checksum[2];    // CSUM
};

struct __attribute__((__packed__)) poe_dev_version_msg_t {
    uint8_t key;            // KEY
    uint8_t echo;           // ECHO
    uint8_t sub;            // SUB
    uint8_t sub1;           // SUB1
    uint8_t prod;           // SUB2
    uint8_t version_h;      // DATA5
    uint8_t version_l;      // DATA6
    uint8_t _data7;         // DATA7
    uint8_t _data8;         // DATA8
    uint8_t _data9;         // DATA9
    uint8_t _data10;        // DATA10
    uint8_t _data11;        // DATA11
    uint8_t _data12;        // DATA12
    uint8_t checksum[2];    // CSUM
};

struct __attribute__((__packed__)) poe_dev_power_supply_msg_t {
    uint8_t key;            // KEY
    uint8_t echo;           // ECHO
    uint8_t power_consump_h;// SUB
    uint8_t power_consump_l;// SUB1
    /* max and min shutdown voltage levels */
    uint8_t max_sd_volt_h;  // SUB2
    uint8_t max_sd_volt_l;  // DATA5
    uint8_t min_sd_volt_h;  // DATA6
    uint8_t min_sd_volt_l;  // DATA7
    uint8_t _data8;         // DATA8
    uint8_t power_bank;     // DATA9
    uint8_t total_power_h;  // DATA10
    uint8_t total_power_l;  // DATA11
    uint8_t _data12;        // DATA12
    uint8_t checksum[2];    // CSUM
};

static struct UartDevice uart_fd;
static int msg_echo;

/*
 * Start the UART device.
 *
 * @param dev points to the UART device to be started, must have filename and rate populated
 * @param canonical whether to define some compatibility flags for a canonical interface
 *
 * @return - 0 if the starting procedure succeeded
 *         - negative if the starting procedure failed
 */
int uart_start(struct UartDevice* dev, bool canonical)
{
    int fd;

    strncpy(dev->filename, "/dev/ttyS1", sizeof(uart_fd.filename));
    fd = open(dev->filename, O_RDWR);
    if (fd < 0) {
        LOG_ERROR("failed to open UART device");
        return fd;
    }

    if (tcgetattr(fd, &dev->tty) != 0)
    {
        LOG_ERROR("error %d from tcgetattr", errno);
        close(fd);
        return -1;
    }

    /*
    "name": "/dev/ttyS1",
    "buadrate": 19200,
    "stopbits": serial.STOPBITS_ONE,
    "parity": serial.PARITY_NONE,
    "timeout": 1 */

    dev->tty.c_cflag = (dev->tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    dev->tty.c_iflag &= ~IGNBRK;         // disable break processing
    dev->tty.c_lflag = 0;                // no signaling chars, no echo,
    dev->tty.c_oflag = 0;                // no remapping, no delays
    dev->tty.c_cc[VMIN]  = 0;            // read doesn't block
    dev->tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    dev->tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    dev->tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    dev->tty.c_cflag &= ~PARENB;      // shut off parity
    dev->tty.c_cflag &= ~CSTOPB;

    cfsetspeed(&dev->tty, B19200);

    if (tcsetattr(fd, TCSANOW, &dev->tty) != 0)
    {
        LOG_ERROR("error %d from tcsetattr", errno);
        close(fd);
        return -1;
    }

    dev->fd = fd;
    return 0;
}

/*
 * Read a string from the UART device.
 *
 * @param dev points to the UART device to be read from
 * @param buf points to the start of buffer to be read into
 * @param buf_len length of the buffer to be read
 *
 * @return - number of bytes read if the read procedure succeeded
 *         - negative if the read procedure failed
 */
int uart_readn(struct UartDevice* dev, uint8_t *buf, size_t buf_len)
{
    int rc;

    rc = read(dev->fd, buf, buf_len);
    if (rc < 0) {
        LOG_ERROR("%s: failed to read uart data, errno: %d", __func__, errno);
        return rc;
    }

    /*
    printf("read: \n\t");
    for (int x = 0; x < rc; x++)
        printf("%02x ", buf[x]);
    printf("\n");
    */

    return rc;
}

/*
 * Read a string from the UART device.
 *
 * @param dev points to the UART device to be read from
 * @param buf points to the start of buffer to be read into
 * @param buf_len length of the buffer to be read
 *
 * @return - number of bytes read if the read procedure succeeded
 *         - negative if the read procedure failed
 */
int uart_reads(struct UartDevice* dev, char *buf, size_t buf_len)
{
    int rc;

    rc = read(dev->fd, buf, buf_len - 1);
    if (rc < 0) {
        LOG_ERROR("%s: failed to read uart data, errno: ", __func__, errno);
        return rc;
    }

    buf[rc] = '\0';
    return rc;
}

/*
 * Write data to the UART device.
 *
 * @param dev points to the UART device to be written to
 * @param buf points to the start of buffer to be written from
 * @param buf_len length of the buffer to be written
 *
 * @return - number of bytes written if the write procedure succeeded
 *         - negative if the write procedure failed
 */
int uart_writen(struct UartDevice* dev, const uint8_t *buf, size_t buf_len) {
    /*
    printf("writing: \n\t");
    for (int x = 0; x < buf_len; x++)
        printf("%02x ", buf[x]);
    printf("\n");
    */
    return write(dev->fd, buf, buf_len);
}

/*
 * Write a string to the UART device.
 *
 * @param dev points to the UART device to be written to
 * @param string points to the start of buffer to be written from
 *
 * @return - number of bytes written if the write procedure succeeded
 *         - negative if the write procedure failed
 */
int uart_writes(struct UartDevice* dev, char *string)
{
    size_t len = strlen(string);
    return uart_writen(dev, string, len);
}

/*
 * Stop the UART device.
 *
 * @param dev points to the UART device to be stopped
 */
void uart_stop(struct UartDevice* dev)
{
    close(dev->fd);
}

void set_checksum(struct poe_msg_t *tx_msg)
{
    const uint8_t *ptr = (const uint8_t *)tx_msg;
    uint16_t checksum = 0;
    int i;
    for (i = 0; i < sizeof(*tx_msg) - sizeof(tx_msg->checksum); i++)
    {
        checksum += ptr[i];
    }
    tx_msg->checksum[0] = checksum >> 8;
    tx_msg->checksum[1] = checksum & 0xff;
}

/* echo should be set by caller */
void set_echo(struct poe_msg_t *tx_msg)
{
    // according to PoE PD69200 spec - echo value is a number between 0x00 to 0xFE (0 - 254)
    msg_echo++;
    if (msg_echo >= 0xff)
    {
        msg_echo = 0;
    }
    tx_msg->echo = msg_echo;
}

int build_tx_msg(
    uint32_t opCode32,
    uint8_t dataLen,
    const uint8_t *dataPtr,
    struct poe_msg_t *tx_msg)
{
    if (dataLen > sizeof(tx_msg->data))
    {
        LOG_ERROR("Invalid message length %u", dataLen);
        return -EMSGSIZE;
    }

    memcpy(tx_msg, &opCode32, sizeof(opCode32));
    set_echo(tx_msg);
    /* pad end of message with magic numbers */
    memset(tx_msg->data, POE_PD69200_MSG_N, sizeof(tx_msg->data));
    memcpy(tx_msg->data, dataPtr, dataLen);
    /* last 2 bytes are the checksum */
    set_checksum(tx_msg);

    return 0;
}

bool is_zero(const uint8_t *msg)
{
    struct poe_msg_t tmp = {0};
    return memcmp(msg, &tmp, sizeof(tmp)) == 0;
}

int check_rx_msg(
    const struct poe_msg_t *tx_msg,
    const uint8_t *rx_msg,
    int msg_len
)
{
    struct poe_msg_t tmp;
    const uint8_t *tx = (const uint8_t *)tx_msg;

    if (msg_len != POE_PD69200_MSG_LEN)
    {
        LOG_ERROR("Invalid rx message length %u", msg_len);
        return -1;
    }
    if (is_zero(rx_msg))
    {
        LOG_ERROR("rx message was not read back properly");
        return -1;
    }
    if ((tx_msg->key == POE_PD69200_MSG_KEY_COMMAND && rx_msg[0] != POE_PD69200_MSG_KEY_REPORT) ||
        (tx_msg->key == POE_PD69200_MSG_KEY_REQUEST && rx_msg[0] != POE_PD69200_MSG_KEY_TELEMETRY))
    {
        LOG_ERROR("Mismatch tx/rx key field: %02x/%02x", tx_msg->key, rx_msg[0]);
        goto err;
    }
    if (rx_msg[1] != tx_msg->echo)
    {
        LOG_ERROR("Mismatch tx/rx echo: %u/%u", tx_msg->echo, rx_msg[1]);
        goto err;
    }

    memcpy(&tmp, rx_msg, sizeof(tmp));
    set_checksum(&tmp);
    if (tmp.checksum[0] != rx_msg[POE_PD69200_MSG_LEN - 2] ||
        tmp.checksum[1] != rx_msg[POE_PD69200_MSG_LEN - 1])
    {
        LOG_ERROR("Invalid rx checksum");
        goto err;
    }

    return 0;
err:
    LOG_ERROR("tx: " MSG_BYTES, MSG_TO_PRINT(tx));
    LOG_ERROR("rx: " MSG_BYTES, MSG_TO_PRINT(rx_msg));
    return -1;
}

int communicate(
    struct poe_msg_t *tx_msg,
    uint8_t *rx_msg
)
{
    uint8_t buf[64];
    int count;
    int rc = 0;

    for (count = 0; count < POE_PD69200_COMM_RETRY_TIMES; count++)
    {
        if ((rc = uart_writen(&uart_fd, (uint8_t *)tx_msg, sizeof(*tx_msg))) < 0)
        {
            LOG_ERROR("Failed to send message");
            goto retry;
        }
        usleep(40*1000);  // 40ms
        // Flush the output queue to ensure all data is sent before the next read
        if (tcflush(uart_fd.fd, TCOFLUSH) == -1)
        {
            LOG_ERROR("Error flushing output queue");
            goto retry;
        }
        if ((rc = uart_readn(&uart_fd, (uint8_t *)rx_msg, POE_PD69200_MSG_LEN)) < 0)
        {
            LOG_ERROR("Failed to receive message");
            goto retry;
        }
        // sometimes we only get half of a message, so try to read the rest of it before failing
        if (rc < POE_PD69200_MSG_LEN)
        {
            LOG_PRINT("expected longer message, trying to read the rest of it");
            int len = rc;
            uint8_t *ptr = (uint8_t *)rx_msg;
            ptr = &ptr[len];
            usleep(40*1000);  // 40ms
            if ((rc = uart_readn(&uart_fd, ptr, POE_PD69200_MSG_LEN - len)) < 0)
            {
                LOG_ERROR("Failed to receive message");
                goto retry;
            }
            rc += len;
        }
        // Flush the input queue to discard any unwanted data in the input buffer
        if (tcflush(uart_fd.fd, TCIFLUSH) == -1)
        {
            LOG_ERROR("Error flushing input queue");
            goto retry;
        }
        LOG_PRINT("received message %d bytes long", rc);
        if (check_rx_msg(tx_msg, rx_msg, rc) != 0)
        {
            goto retry;
        }
        return 0;
retry:
        // clear buffer
        uart_readn(&uart_fd, buf, sizeof(buf));
        // increment echo
        set_echo(tx_msg);
        // update checksum since we incremented echo
        set_checksum(tx_msg);
        // wait a little
        usleep(40*1000);  // 40ms
        // try again
    }
    LOG_ERROR("Failed to send message");
    return rc;
}

bool parse_rx_msg(
    const uint8_t *msg,
    uint8_t msg_type,
    uint8_t *dataPtr
)
{
    switch (msg_type)
    {
    case POE_PD69200_BT_MSG_SUB1_PORTS_PARAMETERS:
    {
        struct poe_port_status_msg_t *port_params_msg = (struct poe_port_status_msg_t *)msg;
        /* LOG_PRINT("port #%2u: [enabled? %u; status %02x; opmode %u; prio %u]",
            dataPtr[0],
            port_params_msg->enabled,
            port_params_msg->status,
            port_params_msg->opmode,
            port_params_msg->priority
        ); */
        /* FIXME: dont use magic numbers */
        dataPtr[1] = port_params_msg->status;
        dataPtr[2] = port_params_msg->enabled;
        dataPtr[3] = port_params_msg->opmode;
        dataPtr[4] = port_params_msg->priority;
        break;
    }
    case POE_PD69200_BT_MSG_SUB1_PORTS_CLASS:
    {
        struct poe_port_class_msg_t *port_class_msg = (struct poe_port_class_msg_t *)msg;
        uint16_t *powerLimitMw;
        dataPtr[1] = port_class_msg->measured_class;
        dataPtr[2] = port_class_msg->class;
        powerLimitMw = (uint16_t *)&dataPtr[3];  /* TODO: check if this is actually alligned */
        *powerLimitMw = port_class_msg->power_limit_h << 8 | port_class_msg->power_limit_l;
        /* LOG_PRINT("port #%2u: [class %02x; measured %02x; pwr limit %u]",
            dataPtr[0],
            port_class_msg->class,
            port_class_msg->measured_class,
            *powerLimitMw
        ); */
        break;
    }
    case POE_PD69200_BT_MSG_SUB1_PORTS_MEASUREMENT:
    {
        struct poe_port_measurement_msg_t *measurement_msg = (struct poe_port_measurement_msg_t *)msg;
        uint16_t *current, *consump, *voltage;
        current = (uint16_t *)&dataPtr[1];
        consump = (uint16_t *)&dataPtr[3];
        voltage = (uint16_t *)&dataPtr[5];
        *current = measurement_msg->current_h << 8 | measurement_msg->current_l;
        *consump = (measurement_msg->consump_h << 8 | measurement_msg->consump_l) * 100;
        *voltage = (measurement_msg->voltage_h << 8 | measurement_msg->voltage_l) * 100;
        /* LOG_PRINT("port #%2u: [current %u; consump %u; voltage %u]",
            dataPtr[0],
            *current,
            *consump,
            *voltage
        ); */
        break;
    }
    case POE_PD69200_MSG_SUB1_VERSIONZ:
    {
        struct poe_dev_version_msg_t *version_msg = (struct poe_dev_version_msg_t *)msg;
        uint16_t version;
        version = version_msg->version_h << 8 | version_msg->version_l;
        dataPtr[1] = version_msg->prod;
        dataPtr[2] = version / 100;
        dataPtr[3] = version / 10 % 10;
        dataPtr[4] = version % 10;
        break;
    }
    case POE_PD69200_MSG_SUB1_SUPPLY:
    {
        struct poe_dev_power_supply_msg_t *power_msg = (struct poe_dev_power_supply_msg_t *)msg;
        uint16_t *power_consumption, *max_sd_volt, *min_sd_volt, *total_power;
        power_consumption = (uint16_t *)&dataPtr[2];
        total_power = (uint16_t *)&dataPtr[4];
        dataPtr[1] = power_msg->power_bank;
        *power_consumption = power_msg->power_consump_h << 8 | power_msg->power_consump_l;  /* Watt */
        *total_power = power_msg->total_power_h << 8 | power_msg->total_power_l;  /* Watt */
        /* LOG_PRINT("dev: [power_consumption %u; total_power %u; used bank %u]",
            *power_consumption,
            *total_power,
            dataPtr[1]
        ); */
        break;
    }
    }
    return true;
}

bool poeUartSendReceiveMsg(
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
)
{
    int rc;
    // LOG_PRINT("opcode: 0x%08x | dataLen: %u", opCode32, dataLen);
    struct poe_msg_t tx_msg = {0};
    uint8_t rx_msg[sizeof(tx_msg)];
    struct poe_port_status_msg_t *port_state;

    if (rc = build_tx_msg(opCode32, dataLen, dataPtr, &tx_msg))
    {
        LOG_ERROR("Failed to create tx message %d", rc);
        return false;
    }
    if (rc = communicate(&tx_msg, rx_msg))
    {
        LOG_ERROR("Failed to send and/or receive message %d", rc);
        return false;
    }

    return parse_rx_msg(rx_msg, tx_msg.sub1, dataPtr);
}

/**
 * @brief Initialize POE UART.
 *
 * @return int Returns error or 0.
 */
int poeUartInit()
{
    int rc;

    rc = uart_start(&uart_fd, false);
    if (rc)
    {
        LOG_ERROR("%s: failed to init uart %d", __func__, rc);
        return -1;
    }
    return 0;
}

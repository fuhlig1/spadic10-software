#ifndef SPADIC_MESSAGE_H
#define SPADIC_MESSAGE_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \file
 * SPADIC 1.0 Message Library
 *
 * Provides functions to extract SPADIC messages from captured raw data
 * and to access the message content.
 */

#include <stddef.h>
#include <stdint.h>

/* create and destroy message objects */
typedef struct _message Message;
/**<
 * Represents SPADIC messages.
 */

Message *message_new(void);
/**<
 * Create and initialize a new message object.
 * \return Pointer to created message object, `NULL` if unsuccessful.
 */

void message_delete(Message *m);
/**<
 * Destroy a message object.
 * Nothing is done if `m` is `NULL`.
 */

size_t message_read_from_buffer(Message *m,
                                const uint16_t *buf, size_t len);
/**<
 * Read words from `buf` and fill message `m`, if possible.
 *
 * The function consumes words from the buffer until either an
 * end-of-message word is encountered or the end of the buffer is reached
 * (i.e. `len` words have been read).
 *
 * The number `n` of consumed words is returned, so that `buf+n` is a
 * suitable value to be passed as the `buf` argument for repeated calls of
 * this function.
 *
 * Four different cases (`a`--`d`) regarding the occurence of words
 * starting or ending a message are possible:
 *
 *     key:
 *         ( = start of message
 *         ) = end of message
 *         x = any word except end of message
 *         . = any word except start of message or end of message
 *         | = end of buffer reached
 *
 *     a:  xxx(....)  normal case
 *     b:  xxx(..|    missing end of message
 *     c:  ........)  missing start of message
 *     d:  ......|    missing start and end of message
 *
 * It is not guaranteed that a complete message was contained in the
 * consumed words (cases b-d), this can be checked afterwards using
 * `message_is_complete(m)`.
 *
 * The passed message object `m` is reset if, and only if, a
 * start-of-message word is encountered. This means
 * - all words before the last start-of-message word are effectively
 *   ignored, and
 * - cases b-d can be handled by passing the same Message object to
 *   successive calls of this function.
 *
 * Reading multiple messages from a buffer could then look something like
 * this:
 *
 * \code{.c}
 * uint16_t *pos = buf;
 * ptrdiff_t left = len;
 * Message *m = message_new();
 *
 * size_t n;
 * while (left > 0) {
 *     n = message_read_from_buffer(m, pos, left);
 *     pos += n;
 *     left -= n;
 *     if (message_is_complete(m)) {
 *         do_something_with(m);
 *     }
 * }
 * \endcode
 */

/* query message type and completeness */
int message_is_hit(const Message *m);
int message_is_hit_aborted(const Message *m);
int message_is_buffer_overflow(const Message *m);
int message_is_epoch_marker(const Message *m);
int message_is_epoch_out_of_sync(const Message *m);
int message_is_info(const Message *m);
int message_is_valid(const Message *m);
int message_is_complete(const Message *m);

/* access message data */
uint8_t message_get_group_id(const Message *m);
uint8_t message_get_channel_id(const Message *m);
uint16_t message_get_timestamp(const Message *m);
int16_t *message_get_samples(const Message *m);
uint8_t message_get_num_samples(const Message *m);
uint8_t message_get_hit_type(const Message *m);
uint8_t message_get_stop_type(const Message *m);
uint8_t message_get_buffer_overflow_count(const Message *m);
uint16_t message_get_epoch_count(const Message *m);
uint8_t message_get_info_type(const Message *m);

#ifdef __cplusplus
}
#endif
#endif

#include <stdlib.h>

#include "message.h"

/* move here again when cleaned up */
#include "message_helper.h"

/* temp */
#include <stdio.h>

/*==== private functions ==========================================*/

void message_init(Message* m)
{
    if (!m) return;
    if (m->data != NULL) {
        free(m->data);
        m->data = NULL;
    }
    m->valid = 0;
}

void message_fill(Message* m, uint16_t w)
{
    if (!m) return;
    Wordtype* t = word_get_type(w);
    if (t != NULL) {
        (t->fill)(m, w);
        m->valid |= t->valid;
    }
}

/*-----------------------------------------------------------------*/

int word_is_type(uint16_t w, Wordtype* t)
{
    return (w & t->mask) == t->value;
}

Wordtype* word_get_type(uint16_t w)
{
    Wordtype* t[9] = {&wSOM, &wTSW, &wRDA, &wEOM, &wBOM, &wEPM, &wEXD,
                      &wINF, &wCON};
    int i;
    for (i=0, i<9, i++) {
        if (word_is_type(w, t[i])) { return t[i] };
    }
    return NULL;
}

int word_is_ignore(uint16_t w)
{
    if (!word_is_type(w, &wINF)) { return 0; }
    else { return word_is_info_type(w, iNOP); }
}

/*==== public functions ===========================================*/

Message* message_new(void)
{
    Message* m;
    m = malloc(sizeof *m);
    message_init(m);
    return m;
}

/*-----------------------------------------------------------------*/

void message_delete(Message* m)
{
    free(m->data);
    free(m);
}

/*-----------------------------------------------------------------*/

size_t message_read_from_buffer(Message* m, uint16_t* buf, size_t len)
{
    uint16_t w;
    size_t n;

    for (n=0; n<len; n++) {
/* 1 */ w = buf[n];
/* 2 */ if (word_is_ignore(w)) { continue; }
/* 3 */ if (word_is_start(w)) { message_init(m); }
/* 4 */ message_fill(m, w);
/* 5 */ if (word_is_end(w)) { break; }
    }
    return n;
}

//        /* start of message -> group ID, channel ID */
//        if (word_is_type(*w, wSOM)) {
//            _m.group_id = (*w & 0x0FF0) >> 4
//            _m.channel_id = (*w & 0x000F);
//            _m.valid |= 0x01;
//
//        /* timestamp */
//        } else if (word_is_type(*w, wTSW)) {
//            _m.timestamp = (*w & 0x0FFF);
//            _m.valid |= 0x02;
//
//        /* data... */
//
//        /* end of message -> num. data, hit type, stop type */
//        } else if (word_is_type(*w, wEOM)) {
//            _m.num_data = (*w & 0x0FC0) >> 6;
//            _m.hit_type = (*w & 0x0030) >> 4;
//            _m.stop_type = (*w & 0x0007);
//            _m.valid |= 0x08;
//
//        /* buffer overflow count */
//        } else if (word_is_type(*w, wBOM)) {
//            _m.buffer_overflow_count = (*w & 0x00FF);
//            _m.valid |= 0x10;
//
//        /* epoch marker */
//        } else if (word_is_type(*w, wEPM)) {
//            _m.epoch_count = (*w & 0x0FFF);
//            _m.valid |= 0x20;
//
//        /* info words */
//        } else if (word_is_type(*w, wINF)) {
//            _m.info_type = (*w & 0x0F00) >> 8;
//            if any(word_is_type(*w, t])
//                   for it in ['iDIS', 'iNGT', 'iNBE', 'iMSB']):
//                _m.channel_id = (w & 0x00F0) >> 4
//            } else if ( word_is_type(*w, iSYN)) {
//                _m.epoch_count = (w & 0x00FF)
//        }
//    }
//    return w+1;
//}

/*-----------------------------------------------------------------*/
int message_is_hit(Message* m)
{
    return ((m->valid == (0x01 | 0x02 | 0x08) ||
            ((m->valid == 0x40) && (m->info_type == ;
}

int message_is_buffer_overflow(Message* m)
{
    return (m->valid == (0x01 | 0x02 | 0x10));
}

int message_is_epoch_marker(Message* m)
{
    return (m->valid == (0x01 | 0x20) ||
            m->valid == (0x01 | 0x30)); /* clarification needed */
}

int message_is_info(Message* m)
{
    return (m->valid == 0x30);
}

int message_is_complete(Message* m)
{
    return (message_is_hit(m) ||
            message_is_buffer_overflow(m) ||
            message_is_epoch_marker(m) ||
            message_is_info(m));
//        m->valid == 0x0F || /* normal hit message */
//        m->valid == 0x30 || /* info message */
//     /* m->valid == ... ||                        */
//    0);
}

/*==== test/temp/dummy/wrap =======================================*/

int seek_message_start_all(uint16_t* begin, uint16_t* end)
{
    Message m;
    int count = 0;
    uint16_t* pw = begin;
    while (pw<end) {
        printf("pw: %u\n", pw);
        pw = read_message(pw, end, &m);
        count++;
    }
    return count;
}

/*-----------------------------------------------------------------*/

int seek_message_start_all_wrap(uint16_t* begin, unsigned int length)
{
    return seek_message_start_all(begin, begin+length);
}

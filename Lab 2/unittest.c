#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PirateList.h"

/*
 * Helper: formatted failure output with tabs and debug info.
 * Prints:
 *   FAIL\t<testName>
 *   [indented details + optional list dump]
 */
void handle_failure_pirate_list(const char *testName,
                                List *list,
                                const char *failDetails) {
    printf("FAIL\t%s\n", testName);
    if (failDetails != NULL) {
        printf("      \t%s\n", failDetails);
    }
    if (list != NULL) {
        printf("      \tList contents (for debugging):\n");
        piratelist_print(list);
    }
}

/* Create a writable temp file, write 'content', rewind, and return it. */
static FILE *make_tempfile_with(const char *fallback_path, const char *content) {
    FILE *fp = tmpfile();
    if (fp == NULL) {
        fp = fopen(fallback_path, "w+");
        if (fp == NULL) {
            return NULL;
        }
    }
    if (content && *content) {
        fputs(content, fp);
    }
    rewind(fp);
    return fp;
}

/*------------------ TESTS ------------------*/

void test_piratelist_init() {
    List list;
    piratelist_init(&list);
    if (list.length != 0) {
        handle_failure_pirate_list("test_piratelist_init",
                                   &list,
                                   "Expected length == 0 after piratelist_init");
    } else {
        printf("PASS\ttest_piratelist_init\n");
    }
}

void test_piratelist_add_reads_two_returns_success() {
    List list;
    piratelist_init(&list);

    const char *content =
        "Calico Jack\n"
        "Mary Read\n";

    FILE *fp = make_tempfile_with("unittest_tmp_reads_two.txt", content);
    if (fp == NULL) {
        printf("FAIL\ttest_piratelist_add_reads_two_returns_success\n");
        printf("      \tUnable to create temporary file\n");
        return;
    }

    int ret = piratelist_add(&list, fp);
    fclose(fp);

    int failed = 0;
    if (ret != 1) {
        handle_failure_pirate_list("test_piratelist_add_reads_two_returns_success", &list,
                                   "Expected piratelist_add to return 1 (success)");
        failed = 1;
    }
    if (!failed && list.length != 2) {
        handle_failure_pirate_list("test_piratelist_add_reads_two_returns_success", &list,
                                   "Expected exactly 2 pirates to be added");
        failed = 1;
    }
    if (!failed && (list.pirates[0].pirate_id != 1 || list.pirates[1].pirate_id != 2)) {
        handle_failure_pirate_list("test_piratelist_add_reads_two_returns_success", &list,
                                   "Expected IDs 1 and 2 in order");
        failed = 1;
    }
    if (!failed && strcmp(list.pirates[0].name, "Calico Jack\n") != 0) {
        handle_failure_pirate_list("test_piratelist_add_reads_two_returns_success", &list,
                                   "First stored name mismatch");
        failed = 1;
    }
    if (!failed && strcmp(list.pirates[1].name, "Mary Read\n") != 0) {
        handle_failure_pirate_list("test_piratelist_add_reads_two_returns_success", &list,
                                   "Second stored name mismatch");
        failed = 1;
    }

    if (!failed) {
        printf("PASS\ttest_piratelist_add_reads_two_returns_success\n");
    }
}

void test_piratelist_add_capacity_returns_zero() {
    List list;
    piratelist_init(&list);

    /* Build a file with more than MAX_PIRATES entries. */
    char bigbuf[LINE_MAX * (MAX_PIRATES + 5)];
    bigbuf[0] = '\0';
    for (int i = 1; i <= MAX_PIRATES + 5; i++) {
        char line[LINE_MAX];
        int n = snprintf(line, sizeof(line), "Pirate %d\n", i);
        if (n < 0 || n >= (int)sizeof(line)) {
            printf("FAIL\ttest_piratelist_add_capacity_returns_zero\n");
            printf("      \tName formatting overflow\n");
            return;
        }
        strcat(bigbuf, line);
    }

    FILE *fp = make_tempfile_with("unittest_tmp_capacity.txt", bigbuf);
    if (fp == NULL) {
        printf("FAIL\ttest_piratelist_add_capacity_returns_zero\n");
        printf("      \tUnable to create temporary file\n");
        return;
    }

    int ret = piratelist_add(&list, fp);
    fclose(fp);

    int failed = 0;
    if (ret != 0) {
        handle_failure_pirate_list("test_piratelist_add_capacity_returns_zero", &list,
                                   "Expected piratelist_add to return 0 when capacity is hit");
        failed = 1;
    }
    if (!failed && list.length != MAX_PIRATES) {
        handle_failure_pirate_list("test_piratelist_add_capacity_returns_zero", &list,
                                   "List length should stop at MAX_PIRATES");
        failed = 1;
    }
    if (!failed) {
        /* First and last entries sanity checks */
        if (strcmp(list.pirates[0].name, "Pirate 1\n") != 0) {
            handle_failure_pirate_list("test_piratelist_add_capacity_returns_zero", &list,
                                       "First stored name mismatch (expected 'Pirate 1\\n')");
            failed = 1;
        } else {
            char expect_last[LINE_MAX];
            snprintf(expect_last, sizeof(expect_last), "Pirate %d\n", MAX_PIRATES);
            if (strcmp(list.pirates[MAX_PIRATES - 1].name, expect_last) != 0) {
                handle_failure_pirate_list("test_piratelist_add_capacity_returns_zero", &list,
                                           "Last stored name mismatch");
                failed = 1;
            }
        }
    }
    if (!failed) {
        /* IDs should be sequential 1..MAX_PIRATES */
        for (int i = 0; i < MAX_PIRATES; i++) {
            if (list.pirates[i].pirate_id != i + 1) {
                handle_failure_pirate_list("test_piratelist_add_capacity_returns_zero", &list,
                                           "IDs not sequential");
                failed = 1;
                break;
            }
        }
    }

    if (!failed) {
        printf("PASS\ttest_piratelist_add_capacity_returns_zero\n");
    }
}

void test_piratelist_add_empty_file_success_zero_added() {
    List list;
    piratelist_init(&list);

    FILE *fp = make_tempfile_with("unittest_tmp_empty.txt", "");
    if (fp == NULL) {
        printf("FAIL\ttest_piratelist_add_empty_file_success_zero_added\n");
        printf("      \tUnable to create temporary file\n");
        return;
    }

    int ret = piratelist_add(&list, fp);
    fclose(fp);

    int failed = 0;
    if (ret != 1) {
        handle_failure_pirate_list("test_piratelist_add_empty_file_success_zero_added", &list,
                                   "Expected piratelist_add to return 1 on empty (no capacity hit)");
        failed = 1;
    }
    if (!failed && list.length != 0) {
        handle_failure_pirate_list("test_piratelist_add_empty_file_success_zero_added", &list,
                                   "Empty file should result in length == 0");
        failed = 1;
    }

    if (!failed) {
        printf("PASS\ttest_piratelist_add_empty_file_success_zero_added\n");
    }
}

void test_piratelist_print_safe() {
    List list;
    piratelist_init(&list);

    FILE *fp = make_tempfile_with("unittest_tmp_print.txt",
                                  "Anne Bonny\n"
                                  "Mary Read\n");
    if (fp == NULL) {
        printf("FAIL\ttest_piratelist_print_safe\n");
        printf("      \tUnable to create temporary file\n");
        return;
    }

    int ret = piratelist_add(&list, fp);
    fclose(fp);

    if (ret != 1) {
        handle_failure_pirate_list("test_piratelist_print_safe", &list,
                                   "Expected piratelist_add to return 1 (no capacity hit)");
        return;
    }

    /* We don't assert on output content; just ensure no crash */
    piratelist_print(&list);
    printf("PASS\ttest_piratelist_print_safe\n");
}

/*------------------ MAIN ------------------*/

int main(void) {
    test_piratelist_init();
    test_piratelist_add_reads_two_returns_success();
    test_piratelist_add_capacity_returns_zero();
    test_piratelist_add_empty_file_success_zero_added();
    test_piratelist_print_safe();

    printf("All tests completed!\n");
    return 0;
}

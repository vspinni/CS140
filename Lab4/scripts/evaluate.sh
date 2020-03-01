#!/bin/sh

for collision in Linear Double ; do
  for table_size in \
      419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 \
      503 509 521 523 541 547 557 563 569 571 577 587 593 599 \
      601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 \
      701 709 719 727 733 739 743 751 757 761 769 773 787 797 \
      809 811 821 823 827 829 839 ; do
    echo $collision $table_size \
    `( cat files/Pictures-SHA1.txt ; echo TP ) | bin/hash_tester $table_size Last7 $collision`
 done
done

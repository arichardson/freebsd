#!/bin/sh

# Remove unnecessary phabricator tags from the commit at HEAD.
# Based on the arcfilter.sh script from LLVM.
git log -1 --pretty=%B | \
  sed 's/^Summary://' | \
  awk '/Reviewers:|Subscribers:/{p=1} /Reviewed By:|Differential Revision:/{p=0} !p && !/^Summary:$/ {sub(/^Summary: /,"");print}' | \
  sed -e 's/^Reviewers: /Reviewers:\t/' \
      -e 's/^Reviewed By: /Reviewed By:\t/' \
      -e 's/^Reviewed by: /Reviewed by:\t/' | \
  git commit --amend --date=now -F -

#!/usr/bin/env bash
set -e

REPORT_DIR="coverage"

"$HOME/.platformio/penv/bin/pio" test -e native

mkdir -p "$REPORT_DIR"

"$HOME/.platformio/penv/bin/gcovr" \
  --root . \
  --object-directory .pio/build/native \
  --filter "src/" \
  --html-details "$REPORT_DIR/index.html" \
  --print-summary

echo ""
echo "Relatório HTML gerado em: $REPORT_DIR/index.html"

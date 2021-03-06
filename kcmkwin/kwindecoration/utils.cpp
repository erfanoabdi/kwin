/*
 * Copyright (c) 2019 Valerio Pilo <vpilo@coldshock.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "utils.h"

#include <KConfigGroup>
#include <KLocalizedString>

namespace
{
const QMap<QString, KDecoration2::BorderSize> s_borderSizes {
    { QStringLiteral("None"),      KDecoration2::BorderSize::None },
    { QStringLiteral("NoSides"),   KDecoration2::BorderSize::NoSides },
    { QStringLiteral("Tiny"),      KDecoration2::BorderSize::Tiny },
    { QStringLiteral("Normal"),    KDecoration2::BorderSize::Normal },
    { QStringLiteral("Large"),     KDecoration2::BorderSize::Large },
    { QStringLiteral("VeryLarge"), KDecoration2::BorderSize::VeryLarge },
    { QStringLiteral("Huge"),      KDecoration2::BorderSize::Huge },
    { QStringLiteral("VeryHuge"),  KDecoration2::BorderSize::VeryHuge },
    { QStringLiteral("Oversized"), KDecoration2::BorderSize::Oversized }
};
const QMap<KDecoration2::BorderSize, QString> s_borderSizeNames {
    { KDecoration2::BorderSize::None,      i18n("No Borders") },
    { KDecoration2::BorderSize::NoSides,   i18n("No Side Borders") },
    { KDecoration2::BorderSize::Tiny,      i18n("Tiny") },
    { KDecoration2::BorderSize::Normal,    i18n("Normal") },
    { KDecoration2::BorderSize::Large,     i18n("Large") },
    { KDecoration2::BorderSize::VeryLarge, i18n("Very Large") },
    { KDecoration2::BorderSize::Huge,      i18n("Huge") },
    { KDecoration2::BorderSize::VeryHuge,  i18n("Very Huge") },
    { KDecoration2::BorderSize::Oversized, i18n("Oversized") }
};

const QHash<KDecoration2::DecorationButtonType, QChar> s_buttonNames {
    {KDecoration2::DecorationButtonType::Menu, QChar('M') },
    {KDecoration2::DecorationButtonType::ApplicationMenu, QChar('N') },
    {KDecoration2::DecorationButtonType::OnAllDesktops, QChar('S') },
    {KDecoration2::DecorationButtonType::ContextHelp, QChar('H') },
    {KDecoration2::DecorationButtonType::Minimize, QChar('I') },
    {KDecoration2::DecorationButtonType::Maximize, QChar('A') },
    {KDecoration2::DecorationButtonType::Close, QChar('X') },
    {KDecoration2::DecorationButtonType::KeepAbove, QChar('F') },
    {KDecoration2::DecorationButtonType::KeepBelow, QChar('B') },
    {KDecoration2::DecorationButtonType::Shade, QChar('L') }
};
}


namespace Utils
{

QString buttonsToString(const DecorationButtonsList &buttons)
{
    auto buttonToString = [](KDecoration2::DecorationButtonType button) -> QChar {
        const auto it = s_buttonNames.constFind(button);
        if (it != s_buttonNames.constEnd()) {
            return it.value();
        }
        return QChar();
    };
    QString ret;
    for (auto button : buttons) {
        ret.append(buttonToString(button));
    }
    return ret;
}

DecorationButtonsList readDecorationButtons(const KConfigGroup &config, const QString &key, const DecorationButtonsList &defaultValue)
{
    auto buttonsFromString = [](const QString &buttons) -> DecorationButtonsList {
        DecorationButtonsList ret;
        for (auto it = buttons.begin(); it != buttons.end(); ++it) {
            for (auto it2 = s_buttonNames.constBegin(); it2 != s_buttonNames.constEnd(); ++it2) {
                if (it2.value() == (*it)) {
                    ret << it2.key();
                }
            }
        }
        return ret;
    };
    return buttonsFromString(config.readEntry(key, buttonsToString(defaultValue)));
}

KDecoration2::BorderSize stringToBorderSize(const QString &name)
{
    auto it = s_borderSizes.constFind(name);
    if (it == s_borderSizes.constEnd()) {
        // non sense values are interpreted just like normal
        return KDecoration2::BorderSize::Normal;
    }
    return it.value();
}

QString borderSizeToString(KDecoration2::BorderSize size)
{
    return s_borderSizes.key(size);
}

const QMap<KDecoration2::BorderSize, QString> &getBorderSizeNames()
{
    return s_borderSizeNames;
}

} // namespace Utils

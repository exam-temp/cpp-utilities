#include "./period.h"

namespace ChronoUtilities {

/*!
 * \class ChronoUtilities::Period
 * \brief Represents a period of time.
 *
 * In contrast to the TimeSpan class, a Period represents a duration between a concrete
 * starting DateTime and end DateTime. Without that context, a Period instance is useless.
 *
 * Note the absence of the TimeSpan::totalYears() and TimeSpan::totalMonth() methods.
 * The reason for this limitation of the TimeSpan class is that the TimeSpan is meant to express
 * a duration independently of the concrete starting DateTime and end DateTime.
 * However, the concrete calendar interval is neccassary for expressing a duration in terms of years
 * and months because not all years and months have the same length.
 *
 * The Period class, on the other hand, expresses the duration between a *concrete* starting DateTime
 * and end DateTime as the number of years, month and days which have been passed **in that particular
 * order**. The accuracy is one day, so the DateTime::timeOfDay() is lost.
 *
 * \remarks The order really matters. For example, the Period between DateTime::fromDateAndTime(1994, 7, 18)
 *          and DateTime::fromDateAndTime(2017, 12, 2) is 23 years, 4 month and 14 days. That means
 *          23 years have been passed, then 4 month and finally 14 days. Adding the 14 days first and then
 *          the 4 month would make a difference of one day because July has 31 days and November only 30.
 */

/*!
 * \brief Constructs a new Period defined by a start DateTime and an end DateTime.
 *
 * The resulting Period will contain the number of years, month and days which have been passed
 * between \a begin and \a end.
 *
 * \todo Pass DateTime objects by value in v5.
 */
Period::Period(const DateTime &begin, const DateTime &end)
{
    m_years = end.year() - beg.year();
    m_months = end.month() - beg.month();
    m_days = end.day() - beg.day();
    if (end.hour() < beg.hour()) {
        --m_days;
    }
    if (m_days < 0) {
        m_days += DateTime::daysInMonth(beg.year(), beg.month());
        --m_months;
    }
    if (m_months < 0) {
        m_months += 12;
        --m_years;
    }
}
} // namespace ChronoUtilities

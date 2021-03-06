/*!
 * \file painter_dashed_stroke_params.hpp
 * \brief file painter_dashed_stroke_params.hpp
 *
 * Copyright 2016 by Intel.
 *
 * Contact: kevin.rogovin@gmail.com
 *
 * This Source Code Form is subject to the
 * terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with
 * this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * \author Kevin Rogovin <kevin.rogovin@gmail.com>
 *
 */

#ifndef FASTUIDRAW_PAINTER_DASHED_STROKE_PARAMS_HPP
#define FASTUIDRAW_PAINTER_DASHED_STROKE_PARAMS_HPP

#include <fastuidraw/painter/shader_data/painter_stroke_params.hpp>
#include <fastuidraw/painter/shader_data/painter_shader_data.hpp>
#include <fastuidraw/painter/shader/painter_dashed_stroke_shader_set.hpp>

namespace fastuidraw
{
/*!\addtogroup PainterShaderData
 * @{
 */

  /*!
   * \brief
   * Class to specify dashed stroking parameters, data is packed
   * as according to PainterDashedStrokeParams::stroke_data_offset_t.
   * Data for dashing is packed [TODO describe].
   */
  class PainterDashedStrokeParams:public PainterItemShaderData
  {
  public:
    /*!
     * \brief
     * Enumeration that provides offsets for the stroking
     * parameters. The dashed pattern is packed in the next
     * block of the data store.
     */
    enum stroke_data_offset_t
      {
        stroke_radius_offset, /*!< offset to dashed stroke radius (packed as float) */
        stroke_miter_limit_offset, /*!< offset to dashed stroke miter limit (packed as float) */
        stroking_units_offset, /*!< Offset to stroking units (packed as uint) */
        stroke_dash_offset_offset, /*!< offset to dash offset value for dashed stroking (packed as float) */
        stroke_total_length_offset, /*!< offset to total legnth of dash pattern (packed as float) */
        stroke_first_interval_start_offset, /*!< offset to value recording the start of the first interval (packed as float) */
        stroke_first_interval_start_on_looping_offset, /*!< offset to value recording the start of the first interval on looping (packed as float) */
        stroke_number_intervals_offset, /*!< offset to value giving the number of intervals (packed as uint) */

        stroke_static_data_size /*!< size of static data for dashed stroking */
      };

    /*!
     * \brief
     * A DashPatternElement is an element of a dash pattern.
     * It specifies how long to draw then how much space to
     * emit before the next DashPatternElement.
     */
    class DashPatternElement
    {
    public:
      /*!
       * Ctor, intializes both \ref m_draw_length and
       * \ref m_space_length as 0.
       */
      DashPatternElement(void):
        m_draw_length(0.0f),
        m_space_length(0.0f)
      {}

      /*!
       * Ctor.
       * \param d value with which to initialize \ref m_draw_length
       * \param s value with which to initialize \ref m_space_length
       */
      DashPatternElement(float d, float s):
        m_draw_length(d),
        m_space_length(s)
      {}

      /*!
       * How long to draw
       */
      float m_draw_length;

      /*!
       * How much space to next DashPatternElement
       */
      float m_space_length;
    };

    /*!
     * Ctor.
     */
    PainterDashedStrokeParams(void);

    /*!
     * Copy ctor.
     */
    PainterDashedStrokeParams(const PainterDashedStrokeParams &obj);

    ~PainterDashedStrokeParams();

    /*!
     * Assignment operator.
     * \param obj value from which to copy
     */
    PainterDashedStrokeParams&
    operator=(const PainterDashedStrokeParams &obj);

    /*!
     * Swap operation
     * \param obj object with which to swap
     */
    void
    swap(PainterDashedStrokeParams &obj);

    /*!
     * The miter limit for miter joins
     */
    float
    miter_limit(void) const;

    /*!
     * Set the value of miter_limit(void) const
     * value is clamped to be non-negative.
     */
    PainterDashedStrokeParams&
    miter_limit(float f);

    /*!
     * The stroking width
     */
    float
    width(void) const;

    /*!
     * Set the value of width(void) const,
     * values are clamped to be non-negative.
     */
    PainterDashedStrokeParams&
    width(float f);

    /*!
     * The stroking radius, equivalent to
     * \code
     * width() * 0.5
     * \endcode
     */
    float
    radius(void) const;

    /*!
     * Set the value of radius(void) const,
     * equivalent to
     * \code
     * width(2.0 * f)
     * \endcode
     */
    PainterDashedStrokeParams&
    radius(float f);

    /*!
     * Returns the units of the stroking, default value is
     * \ref PainterStrokeParams::path_stroking_units
     */
    enum PainterStrokeParams::stroking_units_t
    stroking_units(void) const;

    /*!
     * Set the value of stroking_units(void) const,
     * values are clamped to be non-negative.
     */
    PainterDashedStrokeParams&
    stroking_units(enum PainterStrokeParams::stroking_units_t);

    /*!
     * The dashed offset, i.e. the starting point of the
     * dash pattern to start dashed stroking.
     */
    float
    dash_offset(void) const;

    /*!
     * Set the value of dash_offset(void) const
     */
    PainterDashedStrokeParams&
    dash_offset(float f);

    /*!
     * Returns the dash pattern for stroking.
     */
    c_array<const DashPatternElement>
    dash_pattern(void) const;

    /*!
     * Set the value return by dash_pattern(void) const.
     * \param v dash pattern; the values are -copied-.
     */
    PainterDashedStrokeParams&
    dash_pattern(c_array<const DashPatternElement> v);

    /*!
     * Returns a StrokingDataSelectorBase suitable for PainterDashedStrokeParams.
     * \param pixel_arc_stroking_possible if true, will inform that arc-stroking width
     *                                    in PainterStrokeParams::pixel_stroking_units
     *                                    is possible.
     */
    static
    reference_counted_ptr<const StrokingDataSelectorBase>
    stroking_data_selector(bool pixel_arc_stroking_possible);

    unsigned int
    data_size(void) const override;

    void
    pack_data(c_array<uvec4> dst) const override;

  private:
    void *m_d;
  };
/*! @} */

} //namespace fastuidraw

#endif

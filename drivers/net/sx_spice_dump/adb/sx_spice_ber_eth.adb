<app name="BER">

	<indexes>

		<enum_index name="port_type" reg="">
			<index_type name="Network"   value="0" />
			<index_type name="Near_end_point"   value="1" />
			<index_type name="Internal_RC_LR"   value="2" />
			<index_type name="Far_end"   value="3" />
			<index_type name="USR_main"   value="4" />
			<index_type name="USR_tile"   value="5" />
		</enum_index>

		<enum_index name="grp" reg="">
			<index_type name="IEEE_802_3"   value="0x0" />
			<index_type name="RFC_2863"   value="0x1" />
			<index_type name="RFC_2819"   value="0x2" />
			<index_type name="RFC_3635"   value="0x3" />
			<index_type name="Ethernet_Extended"   value="0x5" />
			<index_type name="Ethernet_Discard"   value="0x6" />
			<index_type name="Link_Level_Retransmission"   value="0x8" />
			<index_type name="Per_Priority"   value="0x10" />
			<index_type name="Per_Traffic_Class"   value="0x11" />
			<index_type name="Physical_layer"   value="0x12" />
			<index_type name="Per_Traffic_Class_Congestion"   value="0x13" />
			<index_type name="Per_Receive_Buffer"   value="0x15" />
			<index_type name="Physical_Layer_Statistical"   value="0x16" />
			<index_type name="Out_of_Band_Port"   value="0x19" />
			<index_type name="InfiniBand_Port"   value="0x20" />
			<index_type name="InfiniBand_Extended_Port"   value="0x21" />
			<index_type name="PLR_counters_group"   value="0x22" />
			<index_type name="RS_FEC_Histogram_group"   value="0x23" />
			<index_type name="USR_XSR_Physical_layer_counters_group"   value="0x24" />
			<index_type name="Infiniband_pkts_counters"   value="0x25" />
		</enum_index>

		<enum_index name="page_select" reg="">
			<index_type name="Operational_info_page"         value="0" />
			<index_type name="Troubleshooting_info_page"     value="1" />
			<index_type name="Phy_info_page"                 value="2" />
			<index_type name="Module_info_page"              value="3" />
			<index_type name="Port_events_page"              value="4" />
			<index_type name="Device_events_page"            value="5" />
			<index_type name="Link_down_info"                value="6" />
			<index_type name="Link_down_events"              value="7" />
			<index_type name="Link_up_info"                  value="8" />
			<index_type name="Module_latched_flag_info_page" value="9" />
			<index_type name="link_down_info_ext"            value="10" />
			<index_type name="mng_debug_page"                value="0xFE" />
			<index_type name="phy_debug_page"                value="0XFF" />
		</enum_index>

		<enum_index name="slot_index" reg="">
			<index_type name="Main_board"		value="0" />
		</enum_index>

		<enum_index name="proto_mask" reg="">
			<index_type name="InfiniBand"	value="0" />
			<index_type name="Ethernet"     value="2" />
		</enum_index>

	</indexes>

	<tree name="ber">
		<hidden_index name="pnat" value="0"/>
		<hidden_index name="swid" value="0"/>
		<hidden_index name="prio_tc" value="0"/>
		<reg name="MSGI"/>
		<reg name="MGIR"/>
		<reg name="MDIR"/>
		<reg name="SPAD"/>
		<seq_index name="local_port" min="1" max="128">
			<reg name="PMDR"/>
			<enum_index name="port_type" reg="">
				<enum_index name="grp" reg="">
					<reg name="PPCNT"/>
				</enum_index>
				<enum_index name="proto_mask" reg="">
					<reg name="PTYS"/>
				</enum_index>
				<enum_index name="page_select" reg="">
					<reg name="PDDR"/>
				</enum_index>
			</enum_index>
		</seq_index>
		<enum_index name="slot_index" reg="">
			<reg name="MVCAP"/>
			<reg name="MTCAP"/>
		</enum_index>
	</tree>
</app>